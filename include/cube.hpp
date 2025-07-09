#pragma once

#include <glm/vec3.hpp>

// Forward declaration
struct worldData;

struct Cube {
    glm::vec3 position;
    bool occupied = false;
    bool isGrounded = false;
};

// Declaration only — implementation in .cpp
bool grounded(Cube _cube, worldData data);
