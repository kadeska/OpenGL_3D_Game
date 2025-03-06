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
    initWindow();
    // main loop. This will be moved into a threaded thread manager
    while (!myWindowManager.shouldClose()) {
        myWindowManager.pollEvents();
        myWindowManager.swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void MyCore::initWindow(){
    if (!myWindowManager.createWindow("My OpenGL App", helper.getScreen_width(), helper.getScreen_height())) {
        return;
    }
}
