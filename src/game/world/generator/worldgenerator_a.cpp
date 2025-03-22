#include "worldgenerator_a.hpp"
#include "../include/filemanager.hpp"

WorldGenerator_A::WorldGenerator_A() {
    helper.log(3, "World Generator_A constructor");
    // Create a vector of Cubes with WORLD_SIZE^3 default-constructed Cube objects.
    // std::vector<Cube> cubeArray(WORLD_SIZE * WORLD_SIZE * WORLD_SIZE, Cube{});

    // Populate the cube array using the world generation algorithm.
    // generateWorld(cubeArray);                                         // i was generating a world here before i was ready.

    // Instance of typeString to convert block types to strings
    //BlockType:: typeConverter;

    // For testing, print block types for the bottom two layers.
    // for (int z = 0; z < 2; ++z) {
    //     std::cout << "Layer " << z << ":\n";
    //     for (int y = 0; y < WORLD_SIZE; ++y) {
    //         for (int x = 0; x < WORLD_SIZE; ++x) {
    //             int idx = index(x, y, z);
    //             std::cout << BlockType::blockTypeToString(cubeArray[idx].blockType) << " ";
    //         }
    //         std::cout << "\n";
    //     }
    //     std::cout << "\n";
    // }
}

int WorldGenerator_A::index(int x, int y, int z) {
    // Compute the 1D index from 3D coordinates.
    return x + WORLD_SIZE * (y + WORLD_SIZE * z);
}

void WorldGenerator_A::generateWorld(std::vector<Cube> world) {
    helper.log(3, "generating world");
    // Iterate over every coordinate in the 3D space.
    for (int z = 0; z < WORLD_SIZE; ++z) {
        for (int y = 0; y < WORLD_SIZE; ++y) {
            for (int x = 0; x < WORLD_SIZE; ++x) {
                helper.log(3, std::string("indexing ( " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(x)));
                int idx = index(x, y, z);
                // Simple generation: the bottom layer is DIRT, the next layer is GRASS.
                if (z == 0) {
                    world[idx].blockType = BlockType::BlockTypes::DIRT;
                } else if (z == 1) {
                    world[idx].blockType = BlockType::BlockTypes::GRASS;
                }
                // Other layers remain EMPTY (default constructed).
            }
        }
    }
    FileManager fm = FileManager();
    fm.saveAsBinary(world, "world.save");  // Change this to be saving an actual World object instead of the vector.
}
