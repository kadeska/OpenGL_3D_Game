#include "mycore.hpp"
#include "../include/helper.hpp"
#include "game/inventory/inventory.hpp"
#include "game/inventory/inventorymanager.hpp"

MyCore::MyCore(std::string config_file_name) {
    configFileName = config_file_name;
    helper.log(3, "MyCore constructor");
    fileManager = new FileManager();
    // load config file if file is valid and loaded correctly
    if (!fileManager->loadConfig(configFileName)) {
        helper.log(1, "oops... something went wrong, shutting down!!");
        return;
    }
    InventoryManager invMan = InventoryManager();

    // At this point everything should be initialized and loaded into memory,
    // Enter render loop after initializing the window.
    // config file has been loaded succesfully, now initialize the window and enter game loop.
    initWindow("window", helper.getScreen_width(), helper.getScreen_height());
}

void MyCore::initWindow(const char* title, int width, int height){
    if (!myWindowManager.createWindow(title, width, height)) {
        return;
    }
}
