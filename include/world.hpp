#pragma once

#include <vector>
#include <glm/vec3.hpp>

class World {
public:
    World(bool shouldMakeDefaultWorld = true, int width = 10, int height = 1, int depth = 10);
    ~World();

    struct worldData
    {
        /* data */
        int tickCount = 0;
        int ID;
        int width;
        int height;
        int depth;
        std::vector<glm::vec3> cubePositions;
    };

    /* Create a default world*/
    worldData createWorld();

    /* Create a world with custom values */
    worldData createWorld(int width, int height, int depth);

    /* get the world data */
    worldData getWorldData() const { return data; }

    void tick();

    void update();

private:
    int someMember;
    worldData data;
};