#pragma once

#include "../src/game/world/world.hpp"
#include <vector>
#include <string>


/**
 * @brief The WorldManager class
 * This class manages multiple worlds in the game.
 * It allows adding, removing, and updating worlds.
 * It also provides access to individual worlds by index.
 * The worlds are stored in a vector, and the class provides methods
 * to manipulate the vector.
 */
class WorldManager {
public:

    
    /**
    * @brief WorldManager constructor
    * This class manages multiple worlds in the game.
    */
    WorldManager();

    /**
     * @brief Add a new world to the manager
     * @param world The world to add
     */
    void addWorld(const World& world);

    /**
     * @brief Get a reference to a world by index
     * @param index The index of the world
     * @return A reference to the world
     */
    World& getWorld(int index);

    /**
     * @brief Remove a world by index
     * @param index The index of the world to remove
     */
    void removeWorld(int index);

    /**
     * @brief Get the number of worlds managed
     * @return The number of worlds
     */
    int getWorldCount() const;


    /**
     * @brief Update the world
     * @param world The world to update
     */
    void updateWorld(World world);

private:
    std::vector<World> worlds; // Vector containing all the worlds
};