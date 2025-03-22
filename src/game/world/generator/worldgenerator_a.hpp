#pragma once
#include <vector>
#include "../include/helper.hpp"
//#include "../include/cube.hpp"

#include "../world.hpp"
//#include "../include/filemanager.hpp"
#include <iostream>

/**
 * @brief The WorldGenerator_A class
 * This class is for generating a basic 20x20x20 world.
 * The algorithm will populate a 3D array of Cubes.
 */
class WorldGenerator_A
{
public:
    WorldGenerator_A();

    // Converts 3D coordinates (x, y, z) to a 1D index.
    int index(int x, int y, int z);

    // Populates the world vector with Cube objects.
    void generateWorld(std::vector<Cube> world);

    // The world dimensions (non-static, per-instance constant).
    const int WORLD_SIZE = 2;
};
