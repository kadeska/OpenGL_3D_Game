#pragma once

#include "world.hpp"
#include "cube.hpp"

#include "worldData.hpp"



/**
 * @brief Physics class to handle physics calculations
 * This class will be responsible for calculating physics
 * such as gravity, collisions, and other physics-related tasks.
 * It will take on an object and calculate its physics based on its properties.
 * This class should directly edit the objects location based off the physics calculations.
 * Will return true of the object has been moved, false if not.
 * 
 */
class Physics {
    public:
        float gravity_multiplier = 0.2f;

        // Will take in an object and calculate its physics such as gravity, collisions, etc.
        bool calculatePhysics(Cube& cube, worldData& world_data, float deltaTime); 

};