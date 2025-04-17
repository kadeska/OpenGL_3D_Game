#include "mywindowmanager.hpp"
#include "helper.hpp"

// Constructor
MyWindowManager::MyWindowManager() // : glWindow(nullptr)
{
    helper.log(3, "MyWindowManager constructor");
}

// Destructor: Ensure cleanup
MyWindowManager::~MyWindowManager(){}

// Create the window and initialize OpenGL
// This has been moved into myGLwindow
// I can make a vulkan window in the future if I want to.
// doing it this way allows me to expand my needs in the future.
bool MyWindowManager::createWindow(const char* title, int width, int height)
{
    glWindow = new myGLwindow(title, width, height);

    // Ideas of multithreading the windows? Allowing me 
    // to have more than one window open at a time. Although 
    // why would I need more than one window for a game? 
    // I guess I could have a settings window, or a console window. 

    // new myGLwindow("test", 300, 300);
    // new myVulkanWindow("test", 300, 300);
    return glWindow != nullptr;
}

RenderManager* MyWindowManager::getRenderManager() {
    return glWindow ? glWindow->getRenderManager() : nullptr;
}

