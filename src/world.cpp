#include "world.hpp"
#include <iostream>


World::World(bool shouldMakeDefaultWorld, int width, int height, int depth)
{
    std::cout << "Creating World" << std::endl;
    if(shouldMakeDefaultWorld){
        data = createWorld();
    } else {
        // initialize a world with custom values.
        data = createWorld(width, height, depth);
    }
}

World::~World()
{
}

World::worldData World::createWorld()
{
    worldData wd;
    CubeInfo cube;
    wd.ID = 1;
    wd.width = 10;
    wd.height = 1;
    wd.depth = 10;
    // Fill a 3D grid of cubes
    for (int x = 0; x < wd.width; ++x) {
        for (int z = 0; z < wd.depth; ++z) {
            for (int y = 0; y < wd.height; ++y) {
            wd.cubePositions.push_back(glm::vec3(x, y, z));
            pushCube(cube, wd, x, y, z); // Push the cube to the world data
            }
        }
    }
    return wd;
}

World::worldData World::createWorld(int width, int height, int depth)
{
     {
        worldData wd;
        CubeInfo cube;
        wd.ID = 1;
        wd.width = width;
        wd.height = height;
        wd.depth = depth;
        // Fill a 2D grid of cubes at y=0
        for (int x = 0; x < wd.width; ++x) {
            for (int z = 0; z < wd.depth; ++z) {
                for (int y = 0; y < wd.height; ++y) {
                    wd.cubePositions.push_back(glm::vec3(x, y, z));
                    if(y == 2) {
                        pushCube(cube, wd, x, y, z, false); // Push the cube to the world data
                    } else {
                        pushCube(cube, wd, x, y, z); // Push the cube to the world data
                    }
                    
                }
            }
        }
        return wd;
    }
}

void World::tick()
{
    // std::cout << "World tick: " << data.tickCount << std::endl;
    // Increment the tick count and update the world every 100 ticks
    // This is where you would handle game logic, physics, etc.
    data.tickCount++;
    if (data.tickCount % 100 == 0) {
        update();
    }
}

void World::update()
{
    std::cout << "Updating World at tick: " << data.tickCount << std::endl;
    // Here you can update the world state, e.g., move entities, spawn new ones, etc.
    // For now, we will just print the current tick count.
    // You can also modify cube positions or add new cubes here if needed.
    if (!data.cubePositions.empty()) {
        // Pick a random index
        int idx = rand() % data.cubePositions.size();
        // Move the selected cube up by 1 in the y direction
        data.cubePositions[idx].y += 1;
        // data.cubes[idx].occupied = false;
        std::cout << "Moved cube at index " << idx << " up by 1 block." << std::endl;
    }
}


void World::pushCube(CubeInfo& cube, World::worldData& wd, float x, float y, float z, bool occupied) {
            // Create a new cube at the specified position
            // and add it to the world data.
            std::cout << "Pushing cube at: " << x << ", " << y << ", " << z << std::endl;
            cube.position = glm::vec3(x, y, z);
            cube.occupied = occupied;
            wd.cubes.push_back(cube);
            std::cout << "Cube pushed at: " << cube.position.x << ", " << cube.position.y << ", " << cube.position.z << ", " << cube.occupied << std::endl;
}