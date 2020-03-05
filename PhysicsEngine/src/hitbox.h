#pragma once
#include <vector>
#include <array>

#include "surface.h"
#include "../../ObjectEngine/type"


namespace __base_ {
    class __hitbox_ : private node_t {
    public:
        virtual ~__hitbox_() = default;
    };
}

class hitbox_polygon : private __base_::__hitbox_ {
private:
    surface_flat __surface;
    
public:
    hitbox_polygon(std::vector<glm::vec3> vertex) : __surface(vertex) {}
    hitbox_polygon(surface_flat surface) : __surface(surface) {}
};

class hitbox_circle : private __base_::__hitbox_ {
private:
    glm::vec3 __normal;
    glm::vec3 __center;
    float __radius;
    
public:
    hitbox_circle(std::vector<glm::vec3>);
};

class hitbox_cube : private __base_::__hitbox_ {
private:
    std::array<surface_flat, 6> __surface;
    
public:
    hitbox_cube(std::vector<glm::vec3>);
    hitbox_cube(std::array<surface_flat, 6> surface) : __surface(surface) {}
};

class hitbox_pyramid : private __base_::__hitbox_ {
private:
    std::vector<surface_flat> __surface;
    
public:
    hitbox_pyramid(std::vector<glm::vec3>);
    hitbox_pyramid(std::vector<surface_flat> surface) : __surface(surface) {}
};

class hitbox_prism : private __base_::__hitbox_ {
private:
    std::vector<surface_flat> __surface;
    
public:
    hitbox_prism(std::vector<glm::vec3>);
    hitbox_prism(std::vector<surface_flat> surface) : __surface(surface) {}
};

class hitbox_cylinder : private __base_::__hitbox_ {
private:
    std::vector<surface_round> __surface;
    
public:
    hitbox_cylinder(std::vector<glm::vec3>, std::vector<float>);
    hitbox_cylinder(std::vector<surface_round> surface) : __surface(surface) {}
};

class hitbox_cone : private __base_::__hitbox_ {
private:
    std::vector<surface_round> __surface;
    
public:
    hitbox_cone(std::vector<glm::vec3>, std::vector<float>);
    hitbox_cone(std::vector<surface_round> surface) : __surface(surface) {}
};

class hitbox_sphere : private __base_::__hitbox_ {
private:
    std::array<surface_round, 2> __surface;
    
public:
    hitbox_sphere(std::vector<glm::vec3>, std::vector<float>);
    hitbox_sphere(std::array<surface_round, 2> surface) : __surface(surface) {}
};


hitbox_circle::hitbox_circle(std::vector<glm::vec3> vertex) {
    __radius = glm::distance(*(vertex.begin()), *(vertex.begin()+(vertex.size()/2)))/2;
}

hitbox_cube::hitbox_cube(std::vector<glm::vec3> vertex) {
    __surface = { surface_flat({vertex[0], vertex[1], vertex[2]})
                , surface_flat({vertex[0], vertex[1], vertex[4]})
                , surface_flat({vertex[0], vertex[3], vertex[4]})
                , surface_flat({vertex[1], vertex[2], vertex[5]})
                , surface_flat({vertex[2], vertex[3], vertex[6]})
                , surface_flat({vertex[2], vertex[5], vertex[6]}) };
}

hitbox_pyramid::hitbox_pyramid(std::vector<glm::vec3> vertex) {
    int size = (int)vertex.size();
    for (int i = 1; i < size-1; i++) {
        __surface.push_back(surface_flat({vertex[0], vertex[i], vertex[i]}));
    }
    __surface.push_back(surface_flat({vertex[0], vertex[1], vertex[size-1]}));
    __surface.push_back(surface_flat({vertex[1], vertex[2], vertex[3]}));
}
