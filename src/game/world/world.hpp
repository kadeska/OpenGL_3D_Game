#pragma once
#include "../include/cube.hpp"
#include <vector>

class World
{
public:
    World();
    World(int worldSize, const std::vector<Cube>& cubeArray);

    int world_size;

private:
    std::vector<Cube> cubes;  // Store Cube objects here
};
