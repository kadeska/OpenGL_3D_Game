#pragma once

#include "mycore.hpp"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void init();
    void update();
    void render();
    void cleanup();
    void loadConfig();
    void saveConfig();
    // void handleEvents();
    // void handleCollisions();
    // void handlePhysics();
    // void handleAI();
    // void handleAudio();

private:
MyCore* myCore;
    // MyWindowManager* myWindowManager;
    // FileManager* fileManager;
    // WorldGenerator_A* worldGen;
    // InventoryManager* invMan;
    // WorldManager* worldManager;
    // RenderManager* renderManager;
    // GameEventManager* gameEventManager;
    // GameSoundManager* gameSoundManager;

};