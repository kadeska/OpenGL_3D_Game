#include "../include/gameManager.hpp"
#include "../include/helper.hpp"
#include "../include/rendermanager.hpp"
#include "../include/worldManager.hpp"


GameManager::GameManager(WorldGenerator_A* worldGenerator, RenderManager* renderManager)
        : worldGenerator(worldGenerator), renderManager(renderManager) {
        // Initialize other members if needed
        helper.log(3, "GameManager constructor");
    };


GameManager::~GameManager()
{
}

void GameManager::init()
{
    helper.log(3, "GameManager init");
    // load config and initialize game resources
    // If
    worldManager = new WorldManager(); // Create a new world manager
    current_world = worldGenerator->generateWorld("default name", 4, 1); // Generate a default world
    worldManager->addWorld(current_world); // Add the generated world to the world manager
    start(); // Start the game
    
}

void GameManager::start()
{
    // start the game render loop
    while (true) {
        // handleEvents();
        // update(); // Update game logic
        render(); // Render the scene
        // handleCollisions();
        // handlePhysics();
        // handleAI();
        // handleAudio();
    }
}

void GameManager::update()
{
    // update tick for game logic
    worldManager->updateWorld(worldManager->getWorld(0));
}

void GameManager::render()
{
    // call render manager render function passing the world array. 
    // in the future i could only pass what needs to be rendered, 
    // so then i dont waste resources passing the large array every 
    // render call. 
    renderManager->renderScene(worldManager->getWorld(0));
}

void GameManager::cleanup()
{
    // cleanup game resources 
}


void GameManager::loadConfig()
{
}

void GameManager::saveConfig()
{
}
