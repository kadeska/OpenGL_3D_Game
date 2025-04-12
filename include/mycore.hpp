#ifndef MYCORE_HPP
#define MYCORE_HPP

#include "filemanager.hpp"
#include "mywindowmanager.hpp"

//#include "../include/helper.hpp"
//#include "../src/game/inventory/inventory.hpp"
#include "../src/game/inventory/inventorymanager.hpp"
#include "../src/game/world/generator/worldgenerator_a.hpp"
#include "worldManager.hpp"


/**
 * @brief The MyCore class
 * This class is for core functionality, this class will contain, 
 * the game loop(containing core game loop and timers...), 
 * the game manager(containing player, inventory, world manager...), 
 * the window manager(window creation, window event handling), 
 * game event manager(game event manager), 
 * game sound manager, 
 */
class MyCore
{
public:
    /**
     * @brief MyCore
     * Program core loads the config file and starts the window
     * @param config_file_name
     */
    MyCore(std::string config_file_name);
    /**
     * @brief initWindow
     * initialize a window
     *
     * @param title
     * @param width
     * @param height
     */
    void initWindow(const char* title, int width, int height);

    /**
     * @brief genWorld
     * @param world_size
     * This function generates a world of the given size.
     */
    World genWorld(int world_size);

    /**
     * @brief configFileName
     */
    std::string configFileName;

    /**
     * @brief fileManager
     * This class will handle game data files
     */
    FileManager* fileManager;

    /**
     * @brief world
     * This class will handle the world
     */
    WorldGenerator_A worldGen;

    /**
     * @brief invMan
     * This class will handle the inventory
     */
    InventoryManager invMan;

    // window manager
    /**
     * @brief myWindowManager
     * Manages windows
     */
    MyWindowManager myWindowManager;

    // World manager
    WorldManager worldManager;

    // game manager

    // game loop manager

};

#endif // MYCORE_HPP
