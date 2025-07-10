#include "glad/glad.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

#include "filemanager.hpp"
#include "inventory.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/epsilon.hpp>

#include "shader.hpp"
#include "camera.hpp"
#include "world.hpp"

#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>



// Callbacks and input
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera and world
Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
World *myWorld = nullptr;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// // timing
// float deltaTime = 0.0f;
// float lastFrame = 0.0f;
std::chrono::steady_clock::time_point lastFrameTime;
std::chrono::duration<float> deltaTime;


int frameCount = 0;
float angle = 0;


struct Collectible {
    glm::vec3 position;
    bool collected = false;
    float scale = 0.3f; // smaller than normal cubes
};

std::vector<Collectible> collectibles;

int main()
{
    // timing
    // ---
    lastFrameTime = std::chrono::steady_clock::now();
    // ---

    // Before doing any graphics stuff lets do config file stuff
    FileManager fm;
    fm.loadConfig("game_config.txt");

    // World
    myWorld = new World(true, 1, 1, 1); 
    // myWorld = new World();

    // testing inventory
    // Inventory inv; // default constructor
    Inventory inv = Inventory(10); // custom constructor with max size

    // collectibles
    collectibles.push_back({ glm::vec3(2.0f, 1.0f, 5.0f), false, 0.3f });
    collectibles.push_back({ glm::vec3(4.0f, 2.0f, -2.0f), false, 0.5f });
    collectibles.push_back({ glm::vec3(1.0f, 0.0f, 2.0f), false, 0.5f });
    collectibles.push_back({ glm::vec3(6.0f, 3.0f, -5.0f), false, 0.5f });
    collectibles.push_back({ glm::vec3(3.0f, 2.0f, 4.0f), false, 0.5f });
    collectibles.push_back({ glm::vec3(5.0f, 1.0f, -1.0f), false, 0.5f });
    collectibles.push_back({ glm::vec3(2.0f, 5.0f, -3.0f), false, 0.5f });

    // -----------------------------------------------------------------------------------------------------
    // Initialization steps below. This stuff could be moved outside of the main function to 
    // keep things cleaner, but its not needed at the moment. Maybe one day I will clean this up.
    // -----------------------------------------------------------------------------------------------------

    // GLFW setup 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3D Game", NULL, NULL);
    
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Shader. Must be loaded after initializing GLFW and window. 
    // ---------------------------------------------------------
    Shader ourShader("src/shader.vs", "src/shader.fs");
    // ---------------------------------------------------------



    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Cube VAO/VBO
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Textures
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("src/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cout << "Failed to load texture" << std::endl;
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("src/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cout << "Failed to load texture" << std::endl;
    stbi_image_free(data);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // 3D Debug Line VAO/VBO
    unsigned int lineVAO, lineVBO;
    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);

    // Crosshair VAO/VBO (NDC)
    float crosshairVertices[] = {
        -0.02f,  0.0f, 0.0f, 0.0f, 0.0f,
         0.02f,  0.0f, 0.0f, 0.0f, 0.0f,
         0.0f, -0.02f, 0.0f, 0.0f, 0.0f,
         0.0f,  0.02f, 0.0f, 0.0f, 0.0f
    };
    unsigned int crosshairVAO, crosshairVBO;
    glGenVertexArrays(1, &crosshairVAO);
    glGenBuffers(1, &crosshairVBO);
    glBindVertexArray(crosshairVAO);
    glBindBuffer(GL_ARRAY_BUFFER, crosshairVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairVertices), crosshairVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glLineWidth(2.0f);


    // End of initialization steps. 
    // ---------------------------------------------------------------------------------------------------


    // Main render loop
    while (!glfwWindowShouldClose(window))
    { // render loop
        // Timing
        frameCount++;
        // Get the current time
        auto currentTime = std::chrono::steady_clock::now();

        // Calculate the duration between the current time and the last frame time
        deltaTime = currentTime - lastFrameTime;

        // Update lastFrameTime for the next iteration
        lastFrameTime = currentTime;
        // --
        
        // float currentFrame = static_cast<float>(glfwGetTime());
        // deltaTime = currentFrame - lastFrame;
        // lastFrame = currentFrame;

        // myWorld->tick(deltaTime.count());
        myWorld->update(deltaTime.count(), frameCount);
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // Use shader and set camera matrices
        ourShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);
        glm::mat4 view = camera->GetViewMatrix();
        ourShader.setMat4("view", view);

        // --- 3D Debug Line ---
        glm::vec3 start = camera->Position;
        glm::vec3 end = camera->Position + camera->Front * 10.0f;
        float lineVertices[] = {
            start.x, start.y, start.z, 0.0f, 0.0f,
            end.x,   end.y,   end.z,   0.0f, 0.0f
        };
        // glBindVertexArray(lineVAO);
        // glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        ourShader.setMat4("model", glm::mat4(1.0f));
        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);

        // --- Render Cubes ---
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < myWorld->getWorldData().cubes.size(); i++)
        { // render cubes
            // if the cubes array is null or empty, skip rendering
            // if(myWorld->getWorldData().cubes.empty()) continue;


            // if this cube should be rendered
            if(myWorld->getWorldData().cubes[i].occupied)
            {
                glm::mat4 model = glm::mat4(1.0f); // this is like the identity model matrix. Like the starting point for the model/cube
                model = glm::translate(model, myWorld->getWorldData().cubes[i].position); // This basicaly sets the location/position of the model
                // angle += 0.1f;
                // rotate if needed
                // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f)); // rotates the model by angle on the given axis
                ourShader.setMat4("model", model);// This passes the model matrix to the shader, the vertex shader will use this matrix to transform the cube’s vertices from model space to world space.
                glDrawArrays(GL_TRIANGLES, 0, 36); // this actually tells opengl to draw the cube/model
            }
        }

        for (const auto& item : collectibles) 
        {
            if (item.collected)
                continue; // don't render collected items

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, item.position);
            model = glm::scale(model, glm::vec3(item.scale)); // scale the cube down

            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        // --- Draw Crosshair in NDC ---
        glDisable(GL_DEPTH_TEST);
        ourShader.use();
        ourShader.setMat4("projection", glm::mat4(1.0f));
        ourShader.setMat4("view", glm::mat4(1.0f));
        ourShader.setMat4("model", glm::mat4(1.0f));
        glBindVertexArray(crosshairVAO);
        glLineWidth(2.0f);
        glDrawArrays(GL_LINES, 0, 4);
        glBindVertexArray(0);
        glEnable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &lineVAO);
    glDeleteBuffers(1, &lineVBO);
    glDeleteVertexArrays(1, &crosshairVAO);
    glDeleteBuffers(1, &crosshairVBO);

    glfwTerminate();
    return 0;
}

// Input and callback functions (unchanged from your code)
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    { 
        if (camera && myWorld)
        { 
            auto hit = pickBlock(camera->Position, camera->Front, 10.0f, *myWorld);
            if (hit)
            {
                std::cout << "Block hit at: " << hit->x << ", " << hit->y << ", " << hit->z << std::endl;
                for (size_t i = 0; i < myWorld->getWorldData().cubes.size(); ++i) 
                {
                    const glm::vec3& pos = myWorld->getWorldData().cubes[i].position;
                    if (glm::all(glm::epsilonEqual(pos, glm::vec3(*hit), glm::vec3(0.001f)))) 
                    {
                        auto& cube = myWorld->getWorldData().cubes[i];
                        std::cout << "Cube occupied: " << cube.occupied << std::endl;
                        // manipulate the cube
                        break;
                    }
                }
            }
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(static_cast<float>(yoffset));
}