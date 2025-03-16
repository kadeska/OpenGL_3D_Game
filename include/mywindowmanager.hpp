#ifndef MYWINDOWMANAGER_HPP
#define MYWINDOWMANAGER_HPP

#include "../include/myglwindow.hpp"

#include <stdio.h>
#include <string>

#include <glad/glad.h>

#include <GLFW/glfw3.h> // OpenGL wrapper

#include <GL/gl.h>

/**
 * @brief The MyWindowManager class
 */
class MyWindowManager
{
private:
    // GLFWwindow *window;
    myGLwindow *glWindow;

public:
    MyWindowManager();  // Constructor
    ~MyWindowManager(); // Destructor

    bool createWindow(const char* title, int width, int height);
};

#endif // MYWINDOWMANAGER_HPP
