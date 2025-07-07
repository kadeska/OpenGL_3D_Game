#pragma once

#include <glm/vec3.hpp>

/**
 * CubeInfo struct holds information about a cube in the world. 
 * This struct can represent a cube and all the data related to it. 
 */
struct Cube {
    glm::vec3 position;
    bool occupied = false;
    // Add more fields as needed, e.g.:
    // int type;
    // float health;
    bool isGrounded = false;
};