#include "world.hpp"
#include <vector>

World::World(int world_size)
{
    helper.log(3, "World constructor");
    // intialize the world size 
    // and create a vector of cubes with the given size if the world is not empty
    // the world can be generated either from file or procedurally
    // if the world is empty, we will generate it procedurally
    size = world_size;
    cubes.resize(size * size * size); // 3D vector of cubes
}

void World::update()
{
    helper.log(3, "World update");
}

Cube World::getCube(int x, int y, int z)
{
    // TODO: insert return statement here
    return cubes[0]; // Placeholder return statement
    // You should implement the logic to return the correct Cube based on x, y, z coordinates.
    // This is just a placeholder to avoid compilation errors.
}

int World::getSize()
{
    return size;
}

std::vector<Cube> &World::getWorld()
{
    return cubes;
}

void World::save(const std::string &filename)
{
}
