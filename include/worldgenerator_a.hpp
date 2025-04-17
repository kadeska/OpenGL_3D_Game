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

    /**
     * @brief generateWorld
     * @param name
     * @param size
     * @param seed
     * @return
     * This function generates a world with the given name, size, and seed.
     */
    World* generateWorld(std::string name = "default name", int size = 50, int seed = 1);

private:
int WORLD_SIZE;
World* world;
};

inline WorldGenerator_A worldGenerator_a;
