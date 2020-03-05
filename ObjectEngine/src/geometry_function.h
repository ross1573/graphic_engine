#pragma once
#include "geometry.h"


template <typename _gT>
_gT make_regular(int size, std::vector<glm::vec3> fragment) {
    std::string __e("GEOMETRY::Unauthorized function access");
    __e += "make_regular(int size, std::vector<glm::vec3> fragment)";
    throw std::runtime_error(__e);
    return _gT();
}

template <typename _gT>
_gT make_regular(int size, glm::vec3 fragment = glm::vec3(0.0f)) {
    std::string __e("GEOMETRY::Unauthorized function access");
    __e += "make_regular(int size, std::vector<glm::vec3> fragment)";
    throw std::runtime_error(__e);
    return _gT();
}

template <>
geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>
make_regular<geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>> (int size, std::vector<glm::vec3> color) {
    std::vector<glm::vec3> __vertex;
    for (int i = 0; i < size; i++) {
        __vertex.push_back(glm::vec3(sin(glm::radians(360.0f/(float)size*(float)i)),
                                     cos(glm::radians(360.0f/(float)size*(float)i)),
                                     0.0f));
    }
    if (color.size() == size) {
        return geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>(__vertex, color);
    }
    return geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>(__vertex, glm::vec3(1.0f));
}

template <>
geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>
make_regular<geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>> (int size, glm::vec3 color) {
    std::vector<glm::vec3> __vertex;
    for (int i = 0; i < size; i++) {
        __vertex.push_back(glm::vec3(sin(glm::radians(360.0f/(float)size*(float)i)),
                                     cos(glm::radians(360.0f/(float)size*(float)i)),
                                     0.0f));
    }
    if (color != glm::vec3(0.0f)) {
        return geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>(__vertex, color);
    }
    return geometry<vertex<__base_::__dimension_<2>, __base_::__texture_<0>>>(__vertex, glm::vec3(1.0f));
}

