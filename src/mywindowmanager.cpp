#include "mywindowmanager.hpp"
#include "helper.hpp"

// Constructor: Initialize window pointer to nullptr
MyWindowManager::MyWindowManager()
    : window(nullptr)
{}

// Destructor: Ensure cleanup
MyWindowManager::~MyWindowManager()
{
    terminate();
}

// Create the window and initialize OpenGL
bool MyWindowManager::createWindow(const std::string &label, int width, int height)
{
    if (!glfwInit()) {
        helper.log(1, "Failed to initialize GLFW");
        return false;
    }

    // Set OpenGL version (if needed)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the GLFW window
    window = glfwCreateWindow(width, height, label.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        helper.log(1, "Failed to create GLFW window");
        return false;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        helper.log(1, "Failed to initialize GLAD");
        return false;
    }

    helper.log(3, "Successfully created window: " + label);
    return true;
}

// Poll events to keep the window responsive
void MyWindowManager::pollEvents()
{
    if (window) {
        glfwPollEvents();
    }
}

// Swap buffers for rendering
void MyWindowManager::swapBuffers()
{
    if (window) {
        glfwSwapBuffers(window);
    }
}

// Check if the window should close
bool MyWindowManager::shouldClose()
{
    return window && glfwWindowShouldClose(window);
}

// Cleanup and terminate GLFW
void MyWindowManager::terminate()
{
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
    helper.log(3, "Window terminated.");
}
