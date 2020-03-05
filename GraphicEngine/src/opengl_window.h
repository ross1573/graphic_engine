#pragma once
#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

#include <string>
#include <functional>
#include <array>
#include <stdexcept>

#include "../../ObjectEngine/type"
    

struct window_settings {
    GLint width                                 = 800;
    GLint height                                = 600;
    const GLchar* title                         = (GLchar*)"window";
    GLfloat version                             = 4.1f;
    GLint msaa                                  = 4;
    
    GLboolean full_screen                       = GL_FALSE;
    GLboolean resizeable                        = GL_FALSE;
    GLboolean vsync                             = GL_TRUE;
    GLboolean transparent                       = GL_FALSE;
    GLboolean menubar                           = GL_TRUE;
};
    

class window {
private:
    GLFWwindow*             __window;
    std::function<void()>   __render;
    
public:
    window(const window_settings& = window_settings());
    window(window_settings&, const std::function<void()>&);
    window(const window&) = delete;
    virtual ~window();
    
    void init(const window_settings& = window_settings());
    void run();
    inline void bind_render(const std::function<void()>&);
    inline void get_window_size(GLint&, GLint&);
};


window::window(const window_settings& settings) {
    init(settings);
}

window::window(window_settings& settings, const std::function<void()>& render)
: __render(render) {
    init(settings);
}

window::~window() {
    glfwTerminate();
}

void window::init(const window_settings& settings) {
    if (glfwInit() == GL_FALSE) {
        std::string __e("OPENGL::Failed to initialize glfw\n");
        __e += "__opengl_core::__init_(const __window_settings&)";
        throw std::runtime_error(__e);
    }
        
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, static_cast<int>(settings.version));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, static_cast<int>(settings.version*10)%10);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, settings.resizeable);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, settings.transparent);
    glfwWindowHint(GLFW_DECORATED, settings.menubar);
    glfwWindowHint(GLFW_SAMPLES, settings.msaa);
        
    GLFWmonitor* monitor = NULL;
    if (settings.full_screen) monitor = glfwGetPrimaryMonitor();
    __window = glfwCreateWindow(settings.width, settings.height, settings.title, monitor, NULL);
    if (__window == NULL) {
        glfwTerminate();
        std::string __e("OPENGL::Failed to create window\n");
        __e += "__opengl_core::__init_(const __window_settings&)";
        throw std::runtime_error(__e);
    }
        
    glfwMakeContextCurrent(__window);
        
    GLint screen_width, screen_height;
    glfwGetFramebufferSize(__window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);
    glfwSwapInterval(settings.vsync);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void window::run() {
    while (!glfwWindowShouldClose(__window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        __render();
        glfwSwapBuffers(__window);
        glfwPollEvents();
    }
}

void window::bind_render(const std::function<void ()>& render) {
    __render = render;
}

void window::get_window_size(GLint& width, GLint& height) {
    glfwGetFramebufferSize(__window, &width, &height);
}
