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

    glfwWindowHint(GLFW_SAMPLES, 4);
    // Set OpenGL version (if needed)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited movement
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    pollEvents();
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // use config values

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it is closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

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
    // Check for Esc key press
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        helper.log(3, "Closing window");
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        terminate();
        // return glfwWindowShouldClose(window);
        return true;
    }
    return glfwWindowShouldClose(window);
}

// Cleanup and terminate GLFW
void MyWindowManager::terminate()
{
    // if (window) {
    //     glfwDestroyWindow(window);
    //     //window = nullptr;
    // }
    glfwTerminate();
    helper.log(3, "Window terminated.");
}
