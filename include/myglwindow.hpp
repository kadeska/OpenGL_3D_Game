#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>
#include <string>

#include "rendermanager.hpp"
#include "gameManager.hpp"
#include "worldgenerator_a.hpp"

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

    
    /**
 * @brief myGLwindow::initWindow
 * This is where most of the magic happens. initialize a GL window, 
 * set context, prepare resources, and enter render loop. 
 * 
 * Lets move the render loop to its own class. 
 * preparing resources could be done in a seperate function to keep it clean. 
 * 
 * @param title
 * @param width
 * @param height
 * @return
 */
    int initWindow(const char* title, int width, int height);
    void processInput(GLFWwindow *window);

    /**
     * @brief renderloop
     * This is the render loop, where all the rendering happens.
     */
    void renderloop();

    RenderManager* getRenderManager() { return renderManager; }

private:
    RenderManager* renderManager;
    Shader* ourShader;
    GLFWwindow* window;
    GameManager* gameManager;
    WorldGenerator_A* worldGenerator_a;
};
