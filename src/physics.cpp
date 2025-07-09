#include "physics.hpp"
#include <iostream>


float maxfloor = 0.0f; // Define a floor level for the physics simulation
// float gravity = 0.1f; // Gravity constant, not used in this simple example


bool Physics::calculatePhysics(Cube& cube, worldData& world_data, float deltaTime) {
    std::cout << "Calculating physics for cube at position " 
    << cube.position.x << ", " 
    << cube.position.y << ", " 
    << cube.position.z << std::endl;
    // do a check to see if the cube is grounded
    if (cube.position.y <= maxfloor || grounded(cube, world_data)) {
        std::cout << "Cube is grounded at position: " 
                  << cube.position.x << ", " 
                  << cube.position.y << ", " 
                  << cube.position.z << std::endl;
        cube.isGrounded = true;
    } else {
        cube.isGrounded = false;
    }

    // if the cube is not grounded, apply gravity
    if(!grounded(cube, world_data)){
        cube.position.y -= gravity_multiplier * deltaTime; // this line gets hit, but the cube doesnt move???
    }
    // cube.position.y -= gravity_multiplier * deltaTime;
    
    return false;
}