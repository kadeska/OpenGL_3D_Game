#include "physics.hpp"


float maxfloor = -2.0f; // Define a floor level for the physics simulation
float gravity = 0.1f; // Gravity constant, not used in this simple example


bool Physics::calculatePhysics(Cube& cube, World::worldData& world) {
    cube.position.y -= gravity; // Simulate gravity by moving the cube down
    if (cube.position.y <= maxfloor){
        cube.position.y = maxfloor;
        cube.isGrounded = true;
        return false;
    } else {
        cube.position.y -= gravity;
        return true;
    }
    return false;
}