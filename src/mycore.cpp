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
    // config file has been loaded succesfully, now initialize the window.
    initWindow("window", helper.getScreen_width(), helper.getScreen_height());
    //Inventory inv = Inventory();
    InventoryManager invMan = InventoryManager();
}

void MyCore::initWindow(const char* title, int width, int height){
    if (!myWindowManager.createWindow(title, width, height)) {
        return;
    }
}
