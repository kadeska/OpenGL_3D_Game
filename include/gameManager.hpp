#pragma once

#include "filemanager.hpp"
#include "worldManager.hpp"
#include "rendermanager.hpp"

// #include "worldgenerator_a.hpp"
#include "../src/game/world/generator/worldgenerator_a.hpp"


class GameManager
{
public:
    GameManager(WorldGenerator_A& worldGenerator, RenderManager* renderManager);

    void generateWorld(int size) {
        worldGenerator.generateWorld(size); // Use the injected instance
    }

    void generateCustomWorld(std::string name, int size, int seed) {
        worldGenerator.generateWorld(name, size, seed); // Use the injected instance
    }

    ~GameManager();

    void init();
    void start();

    void cleanup();
    

private:
    WorldGenerator_A& worldGenerator;
    WorldManager worldManager;
    RenderManager* renderManager;
    
    // World world;
    
    // FileManager fileManager;

    void update();
    void render();
    void loadConfig();
    void saveConfig();
    // void handleEvents();
    // void handleCollisions();
    // void handlePhysics();
    // void handleAI();
    // void handleAudio();

    // MyCore* myCore;
    // MyWindowManager* myWindowManager;
    // FileManager* fileManager;
    // WorldGenerator_A* worldGen;
    // InventoryManager* invMan;
    // WorldManager* worldManager;
    // RenderManager* renderManager;
    // GameEventManager* gameEventManager;
    // GameSoundManager* gameSoundManager;

};