#pragma once
#include <glm/glm.hpp>

#include <vector>

#include "../../ObjectEngine/type"
#include "../../PhysicsEngine/src/compute.h"


namespace __base_ {
    class __surface_ : private node_t {
    public:
        virtual ~__surface_() = default;
    };
}

class surface_flat : private __base_::__surface_ {
protected:
    glm::vec3 __normal;
    std::vector<glm::vec3> __vertex;
    
public:
    surface_flat() = default;
    surface_flat(std::vector<glm::vec3> vertex)
    : __vertex(vertex) {
        __normal = compute_normal(vertex);
    }
};

class surface_round : private __base_::__surface_ {
protected:
    glm::vec3 __normal;
    std::vector<glm::vec3> __vertex;
    float __height;
    
public:
    surface_round() = default;
    surface_round(std::vector<glm::vec3> vertex, float& height)
    : __vertex(vertex)
    , __height(height){
        __normal = compute_normal(vertex);
    }
};


surface_flat make_surface(std::vector<glm::vec3> vertex) {
    return surface_flat(vertex);
}

surface_round make_surface(std::vector<glm::vec3> vertex, float& height) {
    return surface_round(vertex, height);
}

