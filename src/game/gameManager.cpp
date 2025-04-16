#include "../include/gameManager.hpp"
#include "../include/helper.hpp"
//#include "../include/rendermanager.hpp"

#include "../include/worldManager.hpp"


GameManager::GameManager()
{
    helper.log(3, "GameManager constructor");
}

GameManager::~GameManager()
{
}

void GameManager::init()
{
    // load config and initialize game resources
    
}

void GameManager::start()
{
    // start the game render loop
}

void GameManager::update()
{
    // update tick for game logic
}

void GameManager::render()
{
    // call render manager render function passing the world array. 
    // in the future i could only pass what needs to be rendered, 
    // so then i dont waste resources passing the large array every 
    // render call. 
    //renderManager.renderScene(world);
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
