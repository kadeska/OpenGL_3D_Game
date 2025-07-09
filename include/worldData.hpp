#pragma once

#include <vector>

// Forward declare Cube to avoid circular include
struct Cube;

struct worldData {
    int tickCount = 0;
    int ID;
    int width, height, depth;

    std::vector<Cube> cubes;
};
