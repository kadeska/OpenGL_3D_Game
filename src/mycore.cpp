#include "mycore.hpp"

MyCore::MyCore(std::string config_file_name) {
    configFileName = config_file_name;
    helper.log(3, "MyCore constructor");
    fileManager = new FileManager();
    // load config file if file is valid and loaded correctly
    helper.log(3, "testing");
    if (!fileManager->loadConfig(configFileName)) {
        helper.log(1, "oops... something went wrong, shutting down!!");
        return;
    }
    invMan = InventoryManager();

    worldGen = WorldGenerator_A();

    WorldManager worldManager = WorldManager();

    // making a world
    helper.log(3, "Making a world... ");
    // std::vector<Cube> world = std::vector<Cube>(worldGen.WORLD_SIZE*3);
    // worldGen.generateWorld(4); Dont generate world in the constructor.
    // call a game manager class to handle the world generation.
    // but for now I will call genWorld here
    worldManager.addWorld(genWorld(4));
    // genWorld(4);


    // At this point everything should be initialized and loaded into memory,
    // Enter render loop after initializing the window.
    // config file has been loaded succesfully, now initialize the window and enter game loop.
    initWindow("window", helper.getScreen_width(), helper.getScreen_height());
}

void MyCore::initWindow(const char* title, int width, int height){
    helper.log(3, std::string("Init Screen width and height: " + std::to_string(width) + " " + std::to_string(height)));
    if (!myWindowManager.createWindow(title, width, height)) {
        return;
    }
}

World MyCore::genWorld(int world_size)
{
    return *worldGen.generateWorld(world_size);
}
