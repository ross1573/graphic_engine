#pragma once
#include <fstream>

#include "../../GraphicEngine/window"
#include "../../GraphicEngine/shader"
#include "../../GraphicEngine/render"

#include "../../PhysicsEngine/transform"
#include "../../PhysicsEngine/collision"
#include "../../PhysicsEngine/hitbox"

#include "../../ObjectEngine/geometry"
#include "../../ObjectEngine/command"
#include "../../ObjectEngine/type"
#include "../../ObjectEngine/iterator"
#include "../../ObjectEngine/component"

namespace core {


    class __core_graphic {
#ifdef API_OPENGL
    public:
        typedef graphic_window core_t;
        
    private:
        core_t __core;
        
    public:
        __core_graphic(window_settings setting = window_settings())
        : __core(setting, std::bind(&__core_graphic::render, this)) { }
        
        inline void run() {
            setting();
            setup();
            __core.run();
        }
        
        inline std::string get_path() {
            std::string path;
            std::ifstream path_f("PATH.txt");
            if (!path_f.is_open()) {
                std::string __e("CORE::Unable to read PATH.txt\n");
                __e += "__core_graphic::get_path()";
                throw std::runtime_error(__e);
            }
            std::getline(path_f, path);
            path_f.close();
            return path;
        }
        
        inline void get_size(GLint &width, GLint &height) {
            __core.get_window_size(width, height);
        }
        
    protected:
        inline virtual void setting() = 0;
        inline virtual void setup() = 0;
        inline virtual void render() = 0;
#endif
        
#ifdef API_NONE
    public:
        __core_graphic() = default;
        
    protected:
        inline virtual void setting() = 0;
        inline virtual void setup() = 0;
        inline virtual void render() = 0;
#endif
    };
}
