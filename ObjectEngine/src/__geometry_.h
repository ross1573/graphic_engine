#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <memory>

#include "../../ObjectEngine/type"


namespace __base_ {
    class __geometry_ : private node_t {
    public:
        virtual ~__geometry_() = default;
    };

    template <int _tN>
    class __texture_ : private node_t {
        virtual ~__texture_() = default;
    };

    template <int _dN>
    class __dimension_ : private node_t {
        virtual ~__dimension_() = default;
    };
}


template <typename _dT, typename _tT>
struct vertex {
    vertex() = delete;
    vertex(const vertex&) = delete;
    virtual ~vertex() = default;
};

template <>
struct vertex<__base_::__dimension_<2>, __base_::__texture_<0>> {
public:
    glm::vec3 __position;
    glm::vec3 __color;
};

template <>
struct vertex<__base_::__dimension_<2>, __base_::__texture_<1>> {
public:
    glm::vec3 __position;
    glm::vec2 __texcoords;
};


template <typename _vT>
class geometry : private __base_::__geometry_ {
public:
    typedef _vT         vertex_t;
    typedef unsigned    index_t;
    
public:
    geometry() = delete;
    geometry(const geometry&) = delete;
    virtual ~geometry() = default;
};

