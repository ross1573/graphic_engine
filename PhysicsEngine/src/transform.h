#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <map>

#include "../../ObjectEngine/type"
#include "../../ObjectEngine/iterator"

#define TRANSLATE_WEIGHT 0.1f
#define ROTATE_WEIGHT 1.0f
#define SCALE_WEIGHT 0.5f
    

namespace __base_ {
    class __transform_ : private node_t {
    public:
        virtual ~__transform_() = default;
    };
}

class transform : private __base_::__transform_ {
public:
    typedef iterator_map_uint   iterator;
    typedef glm::mat4           model_t;
    typedef float               velocity_t;
    typedef glm::vec3           value_t;
    
private:
    std::map<iterator, model_t> __model;
    unsigned __key_counter;
    
public:
    transform();
    virtual ~transform() = default;
    
    inline iterator insert(const model_t& = model_t(1.0f));
    inline void insert(iterator&, const model_t&);
    inline void replace(const iterator&, const model_t&);
    inline void erase(const iterator&);
    
    inline void translate(iterator&, velocity_t&, value_t&);
    inline void rotate(iterator&, velocity_t&, value_t&);
    inline void scale(iterator&, velocity_t&, value_t&);
    
    inline iterator begin();
    inline iterator end();
    inline model_t find(iterator&);
    
    inline void operator() (iterator&, const model_t&);
    inline iterator operator() (const model_t&);
    
    friend class component;
};


transform::transform()
: __key_counter(0) { }

transform::iterator transform::insert(const model_t& model) {
    __key_counter += 1;
#ifdef DEBUG_MODE
    if (__key_counter == 0) {
        std::string __e("TRANSFORM::Overhead in key\n");
        __e += "__transform_::insert(const id&, const glm::mat4&)";
        throw std::runtime_error(__e);
    }
#endif
    __model.insert(std::make_pair(iterator(__key_counter), model));
    return iterator(__key_counter);
}

void transform::insert(iterator& key, const model_t& model) {
    __key_counter += 1;
#ifdef DEBUG_MODE
    if (__key_counter == 0) {
        std::string __e("TRANSFORM::Overhead in key\n");
        __e += "__transform_::insert(const id&, const glm::mat4&)";
        throw std::runtime_error(__e);
    }
#endif
    key = iterator(__key_counter);
    __model.insert(std::make_pair(key, model));
}



void transform::replace(const iterator &key, const model_t &model) {
#ifdef DEBUG_MODE
    if (__model.find(key) == __model.end()) {
        std::string __e("TRANSFORM::Bad key input\n");
        __e += "__transform_::replace(const id&, const glm::mat4&)";
        throw std::runtime_error(__e);
    }
#endif
    __model.find(key)->second = model;
}

void transform::erase(const iterator &key) {
#ifdef DEBUG_MODE
    if (__model.find(key) == __model.end()) {
        std::string __e("TRANSFORM::Bad key input\n");
        __e += "__transform_::erase(const unsigned&)";
        throw std::runtime_error(__e);
    }
#endif
    __model.erase(key);
}

void transform::translate(iterator& key, velocity_t& velocity, glm::vec3& translate) {
    std::map<iterator, model_t>::iterator __iter = __model.find(key);
#ifdef DEBUG_MODE
    if (__iter == __model.end()) {
        std::string __e("TRANSFORM::Bad key input\n");
        __e += "__transform_::translate(const id&, const glm::vec3&)";
        throw std::runtime_error(__e);
    }
#endif
    __iter->second = glm::translate(__iter->second, translate*velocity*TRANSLATE_WEIGHT);
}

void transform::rotate(iterator &key, velocity_t& velocity, value_t &normal) {
    std::map<iterator, model_t>::iterator __iter = __model.find(key);
#ifdef DEBUG_MODE
    if (__iter == __model.end()) {
        std::string __e("TRANSFORM::Bad key input\n");
        __e += "__transform_::scale(const id&, const glm::vec3&)";
        throw std::runtime_error(__e);
    }
#endif
    __iter->second = glm::rotate(__iter->second, glm::degrees(velocity*ROTATE_WEIGHT), glm::normalize(normal));
}

void transform::scale(iterator& key, velocity_t& velocity, glm::vec3& scale) {
    std::map<iterator, model_t>::iterator __iter = __model.find(key);
#ifdef DEBUG_MODE
    if (__iter == __model.end()) {
        std::string __e("TRANSFORM::Bad key input\n");
        __e += "__transform_::scale(const id&, const glm::vec3&)";
        throw std::runtime_error(__e);
    }
#endif
    __iter->second = glm::scale(__iter->second, scale*velocity*SCALE_WEIGHT);
}

transform::iterator transform::begin() {
    return __model.begin()->first;
}

transform::iterator transform::end() {
    return __model.end()->first;
}

transform::model_t transform::find(iterator &key) {
    return __model.find(key)->second;
}

void transform::operator() (iterator &key, const model_t &model) {
    insert(key, model);
}

transform::iterator transform::operator() (const model_t &model) {
    return insert(model);
}
