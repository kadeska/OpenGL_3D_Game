#include "mycore.hpp"
#include "../include/helper.hpp"

MyCore::MyCore(std::string config_file_name) {
    configFileName = config_file_name;
    helper.log(3, "MyCore constructor");
    fileManager = new FileManager();
    // load config file
    if (!fileManager->loadConfig(configFileName)) {
        helper.log(1, "oops... something went wrong, shutting down!!");
        return;
    }
    initWindow("window", helper.getScreen_width(), helper.getScreen_height());
}

void MyCore::initWindow(const char* title, int width, int height){
    if (!myWindowManager.createWindow(title, width, height)) {
        return;
    }
}
