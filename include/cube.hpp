#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "shader.hpp"

class Cube {
public:
    const int cube_ID;
    const char* cube_str;
    glm::mat4 cube_model;
    float cube_angle;

    /**
     * @brief Cube
     * constructor
     * @param ID
     * pass an ID when initializing a new cube
     * @param str
     * not sure what ill use this for yet.
     */
    Cube(const int ID, const char* str, glm::mat4 model, float angle);
    void render();

private:

};
