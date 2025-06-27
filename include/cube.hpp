#pragma once

#include <glm/vec3.hpp>

struct CubeInfo {
    glm::vec3 position;
    bool occupied = false;
    // Add more fields as needed, e.g.:
    // int type;
    // float health;
};