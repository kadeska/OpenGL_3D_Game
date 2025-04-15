#include "mycore.hpp"

MyCore::MyCore(std::string config_file_name) {
    configFileName = config_file_name;
    helper.log(3, "MyCore constructor");
    // fileManager = new FileManager();
    // load config file if file is valid and loaded correctly
    //helper.log(3, "testing");

    // load program config file, and exit if it fails.
    if (!fileManager.loadConfig(configFileName)) {
        helper.log(1, "oops... something went wrong, shutting down!!");
        return;
    }
    helper.log(2, "Config file loaded successfully");
    helper.log(2, "Config file name: " + configFileName);
    helper.log(2, "Initializing the window...");

    // config file has been loaded succesfully, now initialize the window.
    initWindow("window", helper.getScreen_width(), helper.getScreen_height());
}

void MyCore::initWindow(const char* title, int width, int height){
    helper.log(3, std::string("Initial screen Width and Height: " + std::to_string(width) + " x " + std::to_string(height)));
    // create the window, if fail then exit.
    if (!myWindowManager.createWindow(title, width, height)) {
        return;
    }
}
