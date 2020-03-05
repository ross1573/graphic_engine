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


    class __component_variant {
    public:
        typedef unsigned short shape_id;
        typedef unsigned id;
        typedef glm::mat4 model_t;
            
    private:
        std::vector<std::unique_ptr<shape_t>> __vertex;
        std::vector<std::unique_ptr<render_t>> __render;
        std::map<id, model_t> __model;
        id __key_counter = 0;
        float __rotate = 0.001f;
        
    public:
        template <typename _sT>
        inline shape_id insert(_sT& shape, const shape_id& key = 0);
        inline id insert(const model_t &model = glm::mat4(1.0f), const id &key = 0);
        inline void erase(const shape_id &key);
        inline void erase(const id &key);
        
        inline void translate(const id &key, const glm::vec3 &translate);
        inline void rotate_degree(const id& key, const float& rotate, const glm::vec3& vector);
        inline void rotate(const id& key, const glm::vec3& vector);
        inline void set_degree(const float& degree);
        inline void scale(const id &key, const glm::vec3 &scale);
        
        template <typename _sT>
        inline void draw(_sT &shader);
    };

    
    template <typename _sT>
    unsigned short __component_variant::insert(_sT& shape, const unsigned short& key) {
        if (key == 0) {
            __vertex.push_back(std::make_unique<_sT>(shape));
            std::unique_ptr<render_t> __temp_render = std::make_unique<render_t>();
            __temp_render->insert(shape);
            __render.push_back(std::move(__temp_render));
            return __render.size();
        }
        else {
#ifdef DEBUG_MODE
            if (__vertex.size() < key) {
                std::string __e("COMPONENT::Bad key input\n");
                __e += "__component_variant::insert(_sT&, const unsigned short&)";
                throw std::runtime_error(__e);
            }
#endif
            __vertex[key] = std::make_unique<_sT>(shape);
            __render[key]->insert(shape);
            return key;
        }
        return __render.size();
    }

    unsigned __component_variant::insert(const glm::mat4 &model, const id &key) {
        __key_counter += 1;
#ifdef DEBUG_MODE
        if (__key_counter == 0) {
            std::string __e("COMPONENT::Overhead in key\n");
            __e += "__component_variant::insert(const glm::mat4&, const id&)";
            throw std::runtime_error(__e);
        }
#endif
        if (key == 0) __model.insert(std::make_pair(__key_counter, model));
        else {
#ifdef DEBUG_MODE
            if (__model.find(key) == __model.end()) {
                std::string __e("COMPONENT::Bad key input\n");
                __e += "__component_variant::insert(const glm::mat4&, const id&)";
                throw std::runtime_error(__e);
            }
#endif
            __model.insert(std::make_pair(key, std::move(model)));
            return key;
        }
        return __key_counter;
    }

    void __component_variant::erase(const unsigned &key) {
#ifdef DEBUG_MODE
        if (__model.find(key) == __model.end()) {
            std::string __e("COMPONENT::Bad key input\n");
            __e += "__component_variant::erase(const unsigned&)";
            throw std::runtime_error(__e);
        }
#endif
        __model.erase(key);
    }

    void __component_variant::erase(const unsigned short &key) {
#ifdef DEBUG_MODE
        if (__render.size() < key) {
            std::string __e("COMPONENT::Bad key input\n");
            __e += "__component_variant::erase(const unsigned short&)";
            throw std::runtime_error(__e);
        }
#endif
        std::vector<std::unique_ptr<render_t>>::iterator iter = __render.begin()+(key+1);
        std::vector<std::unique_ptr<shape_t>>::iterator iter2 = __vertex.begin()+(key+1);
        __render.erase(iter);
        __vertex.erase(iter2);
    }

    void __component_variant::translate(const id &key, const glm::vec3 &translate) {
        std::map<id, model_t>::iterator __iter = __model.find(key);
#ifdef DEBUG_MODE
        if (__iter == __model.end()) {
            std::string __e("COMPONENT::Bad key input\n");
            __e += "__component_variant::translate(const id&, const glm::vec3&)";
            throw std::runtime_error(__e);
        }
#endif
        __iter->second = glm::translate(__iter->second, translate);
    }

    void __component_variant::rotate_degree(const id& key, const float& rotate, const glm::vec3& vector) {
            std::map<id, model_t>::iterator __iter = __model.find(key);
    #ifdef DEBUG_MODE
            if (__iter == __model.end()) {
                std::string __e("COMPONENT::Bad key input\n");
                __e += "__component_variant::rotate(const id&, const float&)";
                throw std::runtime_error(__e);
            }
    #endif
            __iter->second = glm::rotate(__iter->second, glm::degrees(rotate), vector);
        }

    void __component_variant::rotate(const id &key, const glm::vec3& vector) {
        std::map<id, model_t>::iterator __iter = __model.find(key);
#ifdef DEBUG_MODE
        if (__iter == __model.end()) {
            std::string __e("COMPONENT::Bad key input\n");
            __e += "__component_variant::rotate(const id&, const float&)";
            throw std::runtime_error(__e);
        }
#endif
        __iter->second = glm::rotate(__iter->second, glm::degrees(__rotate), vector);
    }

    void __component_variant::set_degree(const float &degree) {
        __rotate = degree;
    }

    void __component_variant::scale(const id &key, const glm::vec3 &scale) {
        std::map<id, model_t>::iterator __iter = __model.find(key);
#ifdef DEBUG_MODE
        if (__iter == __model.end()) {
            std::string __e("COMPONENT::Bad key input\n");
            __e += "__component_variant::scale(const id&, const glm::vec3&)";
            throw std::runtime_error(__e);
        }
#endif
        __iter->second = glm::scale(__iter->second, scale);
    }

    template <typename _sT>
    void __component_variant::draw(_sT &shader) {
        shader.use();
        for (auto &model : __model) {
            shader.uniform("model", model.second);
            for (auto &ele : __render) ele->draw();
        }
    }
}
