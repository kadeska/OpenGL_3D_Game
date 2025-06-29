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
    wd.ID       = 1;
    wd.width    = 10;
    wd.height   = 10;
    wd.depth    = 10;
    // Fill a 3D grid of cubes
    for (int x = 0; x < wd.width; ++x) {
        for (int z = 0; z < wd.depth; ++z) {
            for (int y = 0; y < wd.height; ++y) {
            wd.cubePositions.push_back(glm::vec3(x, y, z));
            pushCube(cube, wd, x, y, z, true); // Push the cube to the world data
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
                    // for each position
                    // add the position to the cubePositions vector
                    wd.cubePositions.push_back(glm::vec3(x, y, z));
                    if(y == 2) {
                        // this is just an example of how to use the 
                        // occupied flag to indicate this cube should not
                        // be rendered, or is not occupied. 
                        pushCube(cube, wd, x, y, z, false); // Push the cube to the world data
                    } else {
                        // this is the default case where the cube is occupied.
                        // no need to set occupied to true, it is true by default.
                        pushCube(cube, wd, x, y, z, true); // Push the cube to the world data
                    }
                    
                }
            }
        }

        // // I want to create a small house-like structure
        // // Create a 3x3x3 house structure at position (5, 5, 5)
        // int baseX = 5, baseY = 5, baseZ = 5;
        // // Walls and roof
        // for (int x = 0; x < 5; ++x) {
        //     for (int y = 0; y < 5; ++y) {
        //     for (int z = 0; z < 5; ++z) {
        //         // Place cubes on the outer shell (walls, floor, roof)
        //         if (x == 0 || x == 4 || y == 0 || y == 4 || z == 0 || z == 4) {
        //         // Leave a door opening at (baseX+1, baseY, baseZ)
        //         if (!(x == 1 && y == 0 && z == 1)) {
        //             pushCube(cube, wd, baseX + x, baseY + y, baseZ + z);
        //         }
        //         }
        //     }
        //     }
        // }

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

            // if the given cube is outside of the world bounds, do not push 
            // it to the world data. Also send a warning message.

            if (x < 0 || x >= wd.width || y < 0 || y >= wd.height || z < 0 || z >= wd.depth) {
                std::cerr << "Warning: Cube position out of bounds: " << x << ", " << y << ", " << z << std::endl;
                return;
            }
}