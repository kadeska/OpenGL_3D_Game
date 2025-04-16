#include "worldgenerator_a.hpp"
#include "../include/filemanager.hpp"
#include "../include/helper.hpp"


World* world;

WorldGenerator_A::WorldGenerator_A() {
    helper.log(3, "World Generator_A constructor");
}

World* WorldGenerator_A::generateWorld(int world_size) {
    helper.log(3, "generating world");
    // Create a world object with the specified size.
    world = new World(world_size);
    // Set the world size.
    WORLD_SIZE = world->getSize();  

    // Iterate over every coordinate in the 3D space.
    for (int z = 0; z < WORLD_SIZE; ++z) {
        for (int y = 0; y < WORLD_SIZE; ++y) {
            for (int x = 0; x < WORLD_SIZE; ++x) {  // -----------world generation-----------------
                // debug log of indexing
                helper.log(3, std::string("indexing ( " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(x)));
                // Calculate the index for the current coordinates
                int idx = WorldGenerator::index(x, y, z);

                
                // Add noise generation here ...  
                // int height = noiseGenerator.getHeight(x, y); // Use noise to determine height
                // For now, just set the block type based on the z-coordinate.
                
                
                // Simple generation: the bottom layer is DIRT, the next layer is GRASS.
                if (z == 0) {
                    // set the block type for this layer to DIRT 
                    world->getWorld()[idx].blockType = BlockType::BlockTypes::DIRT;
                    // world.getCube(x, y, z).blockType = BlockType::BlockTypes::DIRT;
                } else if (z == 1) {
                    // set the block type for this layer to GRASS
                    world->getWorld()[idx].blockType = BlockType::BlockTypes::GRASS;
                    // world.getCube(x, y, z).blockType = BlockType::BlockTypes::GRASS;
                }
                // Other layers remain EMPTY (default constructed).
            }
        }
    }
    // FileManager fm = FileManager();
    fileManager.saveAsBinary(world->getWorld(), "world.save"); 
    return world;
}

World* WorldGenerator_A::generateWorld(std::string name, int size, int seed)
{
    // later on I will use the seed to generate a world.
    // This is just a placeholder
    return generateWorld(size);
}
