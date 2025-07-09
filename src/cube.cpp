#include "cube.hpp"
#include "worldData.hpp"
#include <iostream>

bool grounded(Cube _cube, worldData data) {
    // Case 1: On the floor
    if (_cube.position.y <= 0.0f) {
        // std::cout << "Cube is on the floor at position: " 
        //           << _cube.position.x << ", " 
        //           << _cube.position.y << ", " 
        //           << _cube.position.z << std::endl;
        // _cube.isGrounded = true; // Set the grounded status
        return true;
    }

    // Case 2: Check if there's an occupied cube directly below
    for (Cube cube : data.cubes) {
        if (cube.position.x == _cube.position.x &&
            cube.position.z == _cube.position.z &&
            cube.position.y == _cube.position.y - 1 &&
            cube.occupied) {
            // std::cout << "Cube is grounded by another cube at position: " 
            //           << cube.position.x << ", " 
            //           << cube.position.y << ", " 
            //           << cube.position.z << std::endl;
            _cube.isGrounded = true; // Set the grounded status
            return true;
        }
    }

    // Not grounded
    return false;
}
