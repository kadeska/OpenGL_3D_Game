#pragma once

#include "filemanager.hpp"
#include "worldManager.hpp"
#include "rendermanager.hpp"


class GameManager
{
public:
    GameManager();
    ~GameManager();

    void init();
    void start();

    void cleanup();
    

private:
    
    // World world;
    WorldManager worldManager;
    RenderManager* renderManager;
    FileManager fileManager;

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