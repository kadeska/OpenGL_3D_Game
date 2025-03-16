#include "mywindowmanager.hpp"
#include "helper.hpp"

// Constructor: Initialize window pointer to nullptr
MyWindowManager::MyWindowManager()
    : window(nullptr)
{}

// Destructor: Ensure cleanup
MyWindowManager::~MyWindowManager()
{
}

// Create the window and initialize OpenGL
// This has been moved into myGLwindow
// I can make a vulkan window in the future if I want to.
bool MyWindowManager::createWindow(const char* title, int width, int height)
{
    glWindow = new myGLwindow(title, width, height);
    // new myGLwindow("test", 300, 300);
    // new myVulkanWindow("test", 300, 300);
    return true;
}

