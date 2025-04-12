#pragma once
#include <vector>
#include <iostream>
#include "../world.hpp"

/**
 * @brief The WorldGenerator_A class
 * This class is for generating a basic 20x20x20 world.
 * The algorithm will populate a 3D array of Cubes.
 */
class WorldGenerator_A
{
public:
    WorldGenerator_A();

    /**
     * @brief generateWorld
     * @param world_size
     * @return
     * This function generates a world of the given size.
     * It creates a 3D array of Cubes and populates it with block types.
     */
    World* generateWorld(int world_size);

private:
int WORLD_SIZE;
World* world;
};
