#pragma once
#include <glm/glm.hpp>

#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <functional>

#include "../../GraphicEngine/render"
#include "../../ObjectEngine/shape"

namespace obj {


    class __component_unique {
    public:
        typedef unsigned id;
        typedef glm::mat4 model_t;
        
    private:
        std::unique_ptr<shape_t> __vertex;
        std::unique_ptr<render_t> __render;
        std::map<id, model_t> __model;
        id __key_counter = 0;
        float __rotate = 0.001f;
        
    public:
        __component_unique();
        __component_unique(const __component_unique& component) = delete;
        virtual ~__component_unique() = default;
        
        template <typename _sT>
        inline void insert(_sT &shape);
        inline id insert(const model_t &model = glm::mat4(1.0f), const id &key = 0);
        inline void erase(const id &key);
        
        inline void translate(const id &key, const glm::vec3 &translate);
        inline void rotate_degree(const id &key, const float& rotate, const glm::vec3 &vector);
        inline void rotate(const id &key, const glm::vec3 &vector);
        inline void set_degree(const float& degree);
        inline void scale(const id &key, const glm::vec3 &scale);
        
        template <typename _sT>
        inline void draw(_sT &shader);
    };


    __component_unique::__component_unique() {
        __render = std::make_unique<render_t>();
    }

    template <typename _sT>
    void __component_unique::insert(_sT &shape) {
        __vertex = std::make_unique<_sT>(shape);
        __render->insert(shape);
    }

    unsigned __component_unique::insert(const glm::mat4 &model, const id &key) {
            __key_counter += 1;
#ifdef DEBUG_MODE
        if (__key_counter == 0) {
            std::string __e("COMPONENT::Overhead in key\n");
            __e += "__component_unique::insert(const glm::mat4&, const id&)";
            throw std::runtime_error(__e);
        }
#endif
        if (key == 0) __model.insert(std::make_pair(__key_counter, model));
        else {
#ifdef DEBUG_MODE
            if (__model.find(key) == __model.end()) {
                std::string __e("COMPONENT::Bad key input\n");
                __e += "__component_unique::insert(const glm::mat4&, const id&)";
                throw std::runtime_error(__e);
            }
#endif
            __model.insert(std::make_pair(key, std::move(model)));
            return key;
        }
        return __key_counter;
    }

    void __component_unique::erase(const unsigned &key) {
#ifdef DEBUG_MODE
        if (__model.find(key) == __model.end()) {
            std::string __e("COMPONENT::Bad key input\n");
            __e += "__component_unique::erase(const unsigned&)";
            throw std::runtime_error(__e);
        }
#endif
        __model.erase(key);
    }

    void __component_unique::translate(const id &key, const glm::vec3 &translate) {
            std::map<id, model_t>::iterator __iter = __model.find(key);
#ifdef DEBUG_MODE
        if (__iter == __model.end()) {
            std::string __e("COMPONENT::Bad key input\n");
            __e += "__component_unique::translate(const id&, const glm::vec3&)";
            throw std::runtime_error(__e);
        }
#endif
        __iter->second = glm::translate(__iter->second, translate);
    }

    void __component_unique::rotate_degree(const id &key, const float &rotate, const glm::vec3& vector) {
            std::map<id, model_t>::iterator __iter = __model.find(key);
    #ifdef DEBUG_MODE
            if (__iter == __model.end()) {
                std::string __e("COMPONENT::Bad key input\n");
                __e += "__component_unique::rotate(const id&, const float&, const glm::vec3&)";
                throw std::runtime_error(__e);
            }
    #endif
            __iter->second = glm::rotate(__iter->second, glm::degrees(rotate), vector);
        }

    void __component_unique::rotate(const id &key, const glm::vec3& vector) {
        std::map<id, model_t>::iterator __iter = __model.find(key);
#ifdef DEBUG_MODE
        if (__iter == __model.end()) {
            std::string __e("COMPONENT::Bad key input\n");
            __e += "__component_unique::rotate(const id&, const float&, const glm::vec3&)";
            throw std::runtime_error(__e);
        }
#endif
        __iter->second = glm::rotate(__iter->second, glm::degrees(__rotate), vector);
    }

    void __component_unique::set_degree(const float &degree) {
        __rotate = degree;
    }

    void __component_unique::scale(const id &key, const glm::vec3 &scale) {
        std::map<id, model_t>::iterator __iter = __model.find(key);
#ifdef DEBUG_MODE
        if (__iter == __model.end()) {
            std::string __e("COMPONENT::Bad key input\n");
            __e += "__component_unique::scale(const id&, const glm::vec3&)";
            throw std::runtime_error(__e);
        }
#endif
        __iter->second = glm::scale(__iter->second, scale);
    }

    template <typename _sT>
    void __component_unique::draw(_sT &shader) {
        shader.use();
        for (auto &model : __model) {
            shader.uniform("model", model.second);
            __render->draw();
        }
    }
}
