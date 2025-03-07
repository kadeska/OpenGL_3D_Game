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
// This will be moved into myGLwindow
bool MyWindowManager::createWindow(const char* title, int width, int height)
{
    glWindow = new myGLwindow(title, width, height);
    return true;
}

