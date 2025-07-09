#include "physics.hpp"


float maxfloor = -2.0f; // Define a floor level for the physics simulation
// float gravity = 0.1f; // Gravity constant, not used in this simple example


bool Physics::calculatePhysics(Cube& cube, worldData& world_data, float deltaTime) {
    // do a check to see if the cube is grounded
    if (cube.position.y <= maxfloor || grounded(cube, world_data)) {
        cube.isGrounded = true;
    } else {
        cube.isGrounded = false;
    }

    // if the cube is not grounded, apply gravity
    if(!cube.isGrounded){
        cube.position.y -= gravity_multiplier * deltaTime;
    }
    
    return false;
}