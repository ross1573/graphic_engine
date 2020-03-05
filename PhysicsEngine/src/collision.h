#pragma once
#include <glm/glm.hpp>

#include <vector>
#include <array>
#include <memory>
#include <stdexcept>
#include <tuple>

#include "../../ObjectEngine/type"
#include "../../ObjectEngine/geometry"
#include "../../PhysicsEngine/src/compute.h"
#include "../../PhysicsEngine/hitbox"


namespace __base_ {
    class __collision_ : private node_t {
    public:
        virtual ~__collision_() = default;
    };
}


class collision : private __base_::__collision_ {
public:
    typedef hitbox_t                    hitbox_t;
    typedef std::unique_ptr<hitbox_t>   hitbox_ptr;
    typedef std::pair<int, hitbox_ptr>  hitbox_pair;
    
private:
    std::vector<hitbox_pair> __hitbox;
    
public:
    virtual ~collision() = default;
    
    template <typename _hT>
    inline void insert(_hT hitbox);
    
    friend class component;
};


template <typename _hT>
void collision::insert(_hT hitbox) {
    hitbox_ptr __ptr((hitbox_t*)new _hT(hitbox));
    __hitbox.push_back(std::make_pair(type_value<_hT>() , __ptr));
}
