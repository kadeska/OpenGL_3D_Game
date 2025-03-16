#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "../include/rendermanager.hpp"

/**
 * @brief The myGLwindow class
 */
class myGLwindow
{
public:
    /**
     * @brief myGLwindow
     * This creates a OpenGl window
     * @param title
     * @param width
     * @param height
     */
    myGLwindow(const char* title, int width, int height);
    int initWindow(const char* title, int width, int height);
    void processInput(GLFWwindow *window);

private:
    RenderManager* renderManager;
};
