#pragma once
#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <atomic>

#include "../../ObjectEngine/type"


namespace __base_ {
    class __shader_ : private node_t {
    public:
        virtual ~__shader_() = default;
    };
}


class shader : private __base_::__shader_ {
public:
    typedef GLuint              program_t;
    typedef std::string&        path_t;
    typedef GLint               type_t;
    typedef std::string         name_t;
    
private:
    std::vector<program_t>  __shader;
    GLuint                  __program;
    GLboolean               __active;
    
public:
    shader();
    virtual ~shader();
    
    void insert(path_t, type_t);
    void insert(const GLchar*, type_t);
    void erase(int&);
    void compile();
    inline void use();
    
    template <typename _vT>
    void uniform(const name_t&, const _vT&);
    template <typename... _aT>
    inline void uniform(const name_t&, _aT...);
    inline void notify_usage(GLboolean = false);
    
    inline void operator() (path_t, type_t);
    inline void operator() (const GLchar*, type_t);
    
    friend class component;
};


shader::shader()
: __program(0) {
    __active = false;
}

shader::~shader() {
    if (__program) glDeleteProgram(__program);
}

void shader::use() {
    if (!__active) {
        glUseProgram(__program);
        __active = true;
    }
}

void shader::insert(std::string &path, GLint type) {
    GLuint shader;
    std::string code_str;
    std::ifstream file;
    std::stringstream stream;
    const GLchar* code;
    
    GLint success;
    GLchar infoLog[512];
    
    file.exceptions(std::ifstream::badbit);
    try {
        file.open(path.c_str());
        stream << file.rdbuf();
        file.close();
        code_str = stream.str();
    }
    catch (std::ifstream::failure error) {
        std::string __e("SHADER::Error reading shader file\n");
        __e += error.what();
        throw std::runtime_error(__e);
    }
    
    code = code_str.c_str();
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::string __e("SHADER::Error compiling shader\n");
        __e = __e + path + "\n" + infoLog;
        throw std::runtime_error(__e);
    }
    
    __shader.push_back(shader);
}

void shader::insert(const GLchar *path, GLint type) {
    GLuint shader;
    std::string code_str;
    std::ifstream file;
    std::stringstream stream;
    const GLchar* code;
    
    GLint success;
    GLchar infoLog[512];
    
    file.exceptions(std::ifstream::badbit);
    try {
        file.open(path);
        stream << file.rdbuf();
        file.close();
        code_str = stream.str();
    }
    catch (std::ifstream::failure error) {
        std::string __e("SHADER::Error reading shader file\n");
        __e += error.what();
        throw std::runtime_error(__e);
    }
    
    code = code_str.c_str();
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::string __e("SHADER::Error compiling shader\n");
        __e = __e + path + "\n" + infoLog;
        throw std::runtime_error(__e);
    }
    
    __shader.push_back(shader);
}

void shader::compile() {
    GLint success;
    GLchar infoLog[512];
    
    __program = glCreateProgram();
    for (auto &ele : __shader) glAttachShader(__program, ele);
    glLinkProgram(__program);
    glGetProgramiv(__program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(__program, 512, NULL, infoLog);
        std::string __e("SHADER::Error linking shader program\n");
        __e = __e + infoLog;
        throw std::runtime_error(__e);
    }
    
    for (auto &ele : __shader) glDeleteShader(ele);
}

template <>
void shader::uniform(const std::string &name, const glm::mat2 &value) {
    glUniformMatrix2fv(glGetUniformLocation(__program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

template <>
void shader::uniform(const std::string &name, const glm::mat3 &value) {
    glUniformMatrix3fv(glGetUniformLocation(__program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

template <>
void shader::uniform(const std::string &name, const glm::mat4 &value) {
    glUniformMatrix4fv(glGetUniformLocation(__program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

template <>
void shader::uniform(const std::string &name, const glm::vec2 &value) {
    glUniform2f(glGetUniformLocation(__program, name.c_str()), value.x, value.y);
}

template <>
void shader::uniform(const std::string &name, const glm::vec3 &value) {
    glUniform3f(glGetUniformLocation(__program, name.c_str()), value.x, value.y, value.z);
}

template <>
void shader::uniform(const std::string &name, const glm::vec4 &value) {
    glUniform4f(glGetUniformLocation(__program, name.c_str()), value.x, value.y, value.z, value.w);
}

template <>
void shader::uniform(const std::string &name, const GLfloat v0) {
    glUniform1f(glGetUniformLocation(__program, name.c_str()), v0);
}

template <>
void shader::uniform(const std::string &name, GLfloat v0, GLfloat v1) {
    glUniform2f(glGetUniformLocation(__program, name.c_str()), v0, v1);
}

template <>
void shader::uniform(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2) {
    glUniform3f(glGetUniformLocation(__program, name.c_str()), v0, v1, v2);
}

template <>
void shader::uniform(const name_t &name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glUniform4f(glGetUniformLocation(__program, name.c_str()), v0, v1, v2, v3);
}

void shader::notify_usage(GLboolean usage) {
    __active = usage;
}

void shader::operator() (std::string &path, GLint type) {
    insert(path, type);
}

void shader::operator() (const GLchar *path, type_t type) {
    insert(path, type);
}
