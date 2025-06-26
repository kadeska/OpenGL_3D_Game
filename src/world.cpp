#include "world.hpp"
#include <iostream>

World::World()
{
    std::cout << "Creating World" << std::endl;
    data = createWorld();
}

World::~World()
{
}

World::worldData World::createWorld()
{
    worldData wd;
    wd.ID = 1;
    wd.width = 10;
    wd.height = 1;
    wd.depth = 10;
    // Fill a 2D grid of cubes at y=0
    for (int x = 0; x < wd.width; ++x) {
        for (int z = 0; z < wd.depth; ++z) {
            wd.cubePositions.push_back(glm::vec3(x, 0, z));
        }
    }
    return wd;
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
        std::cout << "Moved cube at index " << idx << " up by 1 block." << std::endl;
    }
}
