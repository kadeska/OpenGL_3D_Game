#pragma once

#include <vector>
#include <glm/vec3.hpp>

#include "cube.hpp"
#include "physics.hpp"

#include "worldData.hpp"

// class World;

class World {
public:
    World(bool shouldMakeDefaultWorld = true, int width = 10, int height = 1, int depth = 10);
    ~World();

    float deltaTime;

    

    /* Create a default world*/
    worldData createWorld();

    /* Create a world with custom values */
    worldData createWorld(int width, int height, int depth);

    /* get the world data */
    worldData getWorldData() const { return data; }

    /**
     * Tick function gets called every frame right now, may change in the future to be called every X frames.
     * Increments the tick count and calls the update function every X ticks. X is set inside the function.
     * This function should not be used for logic updates, but rather for timing and scheduling updates.
     */
    void tick();

    /**
     * Update world logic. This function is called every X ticks, set in the tick() function.
     * It can be used to update the world state, such as moving cubes, spawning new cubes, etc.
     */
    void update(float _deltaTime, int frameCount);

    /**
     * Push a cube into the array of cubes in the world data. The cube
     * must be within the bounds of the world, otherwise it will not be
     * pushed to the array of cubes or even be rendered. 
     * It takes the cube struct, world object, cube location, 
     * and an optional boolean flag to indicate if the cube is occupied.
     * This function will initialize the cube's position, and change 
     * the occupied status to true or false based on the given parameter.
     * @param cube The CubeInfo object to push.
     * @param wd The worldData object to which the cube will be added.
     * @param x The x-coordinate of the cube's position.
     * @param y The y-coordinate of the cube's position.
     * @param z The z-coordinate of the cube's position.
     * @param occupied Whether the cube is occupied or not. Default is true. 
     * This is like a flag to indicate if this cube should be rendered or not. 
     * I may change the name of this later but for now this works.
     *
     * @note Tip: Will throw a warning if the cube is outside the world bounds. 
     * make sure the given location data is within the world bounds.
     * The world bounds are defined by the width, height, and depth of the world.
     * 
     */
    void pushCube(Cube& cube, worldData& wd, float x, float y, float z, bool occupied = true);

private:
    int someMember;
    worldData data;
};