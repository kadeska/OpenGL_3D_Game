#pragma once

#include <vector>
#include <glm/vec3.hpp>

class World {
public:
    World();
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

    /* get the world data */
    worldData getWorldData() const { return data; }

    void tick();

    void update();

private:
    int someMember;
    worldData data;
};