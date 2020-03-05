#pragma once
#include <glm/glm.hpp>

#include <vector>
#include <stdexcept>

#include "../../ObjectEngine/type"
#include "__geometry_.h"

class render;

        
template <>
class geometry<vertex<__base_::__dimension_<2>,
                      __base_::__texture_<0>>> : private __base_::__geometry_ {
public:
    typedef vertex<__base_::__dimension_<2>,
                   __base_::__texture_<0>>      vertex_t;
    typedef unsigned                            index_t;
    
private:
    std::vector<vertex_t> __vertex;
    std::vector<index_t>  __index;
    
public:
    geometry() = default;
    geometry(std::vector<glm::vec3>, glm::vec3);
    geometry(std::vector<glm::vec3>, std::vector<glm::vec3>);
    virtual ~geometry() = default;
    
    inline void insert(std::vector<glm::vec3>, glm::vec3);
    inline void insert(std::vector<glm::vec3>, std::vector<glm::vec3>);
    
    inline void translate(glm::vec3);
    inline void rotate(float, glm::vec3 = {0.0f, 0.0f, 1.0f});
    inline void scale(glm::vec3);
    
    inline void operator() (std::vector<glm::vec3>, glm::vec3);
    inline void operator() (std::vector<glm::vec3>, std::vector<glm::vec3>);
    
    friend class render;
    friend class component;
};


geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>::geometry(std::vector<glm::vec3> vertex, glm::vec3 color) {
    insert(vertex, color);
}

geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>::geometry(std::vector<glm::vec3> vertex, std::vector<glm::vec3> color) {
    insert(vertex, color);
}

void geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>::insert(std::vector<glm::vec3> vertex, glm::vec3 color) {
    __vertex.clear();
    for (int i = 0; i < vertex.size(); i++) {
        __vertex.push_back({ vertex[i], color });
    }
    for (int i = 0; i < vertex.size()-2; i++) {
        __index.push_back(0);
        __index.push_back(i+1);
        __index.push_back(i+2);
    }
}

void geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>::insert(std::vector<glm::vec3> vertex, std::vector<glm::vec3> color) {
#ifdef DEBUG_MODE
    if (vertex.size() != color.size()) {
        std::string __e("GEOMETRIC::Incomplete input size\n");
        __e += "geometric_2d::insert(std::vector<glm::vec3>, std::vector<glm::vec3>)";
        throw std::runtime_error(__e);
    }
#endif
    __vertex.clear();
    for (int i = 0; i < vertex.size(); i++) {
        __vertex.push_back({ vertex[i], color[i] });
    }
    for (int i = 0; i < vertex.size()-2; i++) {
        __index.push_back(0);
        __index.push_back(i+1);
        __index.push_back(i+2);
    }
}

void geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>::translate(glm::vec3 translate) {
    for (auto ele : __vertex) {
        ele.__position = glm::vec3(glm::translate(glm::mat4(1.0f), translate)*
                                    glm::vec4(ele.__position, 1.0f));
    }
}

void geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>::rotate(float rotate, glm::vec3 vertex) {
    for (auto ele : __vertex) {
        ele.__position = glm::vec3(glm::rotate(glm::mat4(1.0f), rotate, vertex)*
                                    glm::vec4(ele.__position, 1.0f));
    }
}

void geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>::scale(glm::vec3 scale) {
    for (auto ele : __vertex) {
        ele.__position = glm::vec3(glm::scale(glm::mat4(1.0f), scale)*
                                    glm::vec4(ele.__position, 1.0f));
    }
}

void geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>::operator()(std::vector<glm::vec3> vertex, glm::vec3 color) {
    insert(vertex, color);
}

void geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>::operator()(std::vector<glm::vec3> vertex, std::vector<glm::vec3> color) {
    insert(vertex, color);
}
