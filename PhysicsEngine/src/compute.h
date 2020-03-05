#pragma once
#include <glm/glm.hpp>

#include <vector>
#include <stdexcept>


glm::vec3 compute_normal(std::vector<glm::vec3>& vertex) {
#ifdef DEBUG_MODE
    if (vertex.size() < 3) {
        std::string __e("CALCULATION::Bad input\n");
        __e += "process_normal(std::vector<glm::vec3>&)";
        throw std::runtime_error(__e);
    }
#endif
    return glm::cross(vertex[0]-vertex[1], vertex[1]-vertex[2]);
}
