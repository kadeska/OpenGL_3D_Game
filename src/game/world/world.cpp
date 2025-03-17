#include "world.hpp"

World::World() {}

World::World(int worldSize, const std::vector<Cube>& cubeArray)
    : world_size(worldSize), cubes(cubeArray)
{
    // You can perform additional initialization here if needed.
}
