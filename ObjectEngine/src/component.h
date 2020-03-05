#pragma once
#include <map>
#include <memory>

#include "../../ObjectEngine/type"
    

class component {
public:
    typedef unsigned int                            type_id;
    typedef std::unique_ptr<node_t>                 node_ptr;
    typedef std::map<type_id, node_ptr>             node_map;
    typedef node_map::iterator                      node_iter;
    
    using type_render                               = typename type<typ::RENDER_CLASS>::rtype*;
    using type_shader                               = typename type<typ::SHADER_CLASS>::rtype*;
    using type_transform                            = typename type<typ::TRANSFORM_CLASS>::rtype*;
    using type_collision                            = typename type<typ::COLLISION_CLASS>::rtype*;
    template <typename _vT>
    using type_geometry                             = typename type<type_value<geometry<_vT>>::value>::rtype*;
    
private:
    node_map    __node;
    node_iter   __iter;
    
public:
    virtual ~component() = default;
    
    template <typename _nT> void insert(_nT);
    template <int _tN>      void insert();
                            void erase(type_id);
    template <typename _nT> inline _nT* get();
    template <int _tN>      inline typename type<_tN>::rtype* get();
    
    inline type_render          render();
    inline type_shader          shader();
    inline type_transform       transform();
    inline type_collision       collision();
    template <typename _vT>
    inline type_geometry<_vT>   geometry();
    
    inline void draw();
    
    inline void create_all();
    inline void push();
};


template <typename _nT>
void component::insert(_nT node) {
    __node.insert({type_value<_nT>::value, make_node(node)});
}

template <int _tN>
void component::insert() {
    __node.insert({make_class<_tN>::value, make_node<_tN>()});
}

void component::erase(type_id type) {
    __iter = __node.find(type);
    if (__iter == __node.end()) return;
    __node.erase(__iter);
}

template <typename _nT>
_nT* component::get() {
    return get<type_value<_nT>>();
}

template <int _tN>
typename type<_tN>::rtype* component::get() {
    __iter = __node.find(_tN);
#ifdef DEBUG_MODE
    if (__iter == __node.end()) {
        std::string __e("COMPONENT::Undefined component\n");
        __e += "component::get()";
        throw std::runtime_error(__e);
    }
#endif
    return ::get<_tN>(__iter->second);
}

typename type<typ::RENDER_CLASS>::rtype* component::render() {
    return get<typ::RENDER_CLASS>();
}

typename type<typ::SHADER_CLASS>::rtype* component::shader() {
    return get<typ::SHADER_CLASS>();
}

typename type<typ::TRANSFORM_CLASS>::rtype* component::transform() {
    return get<typ::TRANSFORM_CLASS>();
}

typename type<typ::COLLISION_CLASS>::rtype* component::collision() {
    return get<typ::COLLISION_CLASS>();
}

template <typename _vT>
typename type<type_value<geometry<_vT>>::value>::rtype* component::geometry() {
    return get<typ::GEOMETRY_CLASS | type_value<_vT>::value>();
}

void component::create_all() {
    if (__node.find(typ::RENDER) == __node.end()) insert<typ::RENDER>();
    if (__node.find(typ::SHADER) == __node.end()) insert<typ::SHADER>();
    if (__node.find(typ::TRANSFORM) == __node.end()) insert<typ::TRANSFORM>();
    if (__node.find(typ::COLLISION) == __node.end()) insert<typ::COLLISION>();
}
    
void component::draw() {
    if (__node.find(typ::SHADER_CLASS) != __node.end()) {
        get<typ::SHADER_CLASS>()->use();
    }
    for (auto &ele : get<typ::TRANSFORM_CLASS>()->__model) {
        get<typ::SHADER_CLASS>()->uniform("model", ele.second);
        get<typ::RENDER_CLASS>()->draw();
    }
    get<typ::SHADER_CLASS>()->notify_usage(false);
}
