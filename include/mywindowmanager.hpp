#ifndef MYWINDOWMANAGER_HPP
#define MYWINDOWMANAGER_HPP

#include <stdio.h>
#include <string>

#include <glad/glad.h>

#include <GLFW/glfw3.h> // OpenGL wrapper

#include <GL/gl.h>

class MyWindowManager
{
private:
    GLFWwindow *window;

public:
    MyWindowManager();  // Constructor
    ~MyWindowManager(); // Destructor

    bool createWindow(const std::string &label, int width, int height);
    void pollEvents();
    void swapBuffers();
    bool shouldClose();
    void terminate();
};

#endif // MYWINDOWMANAGER_HPP
