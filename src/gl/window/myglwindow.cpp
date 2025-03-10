#include "../include/myglwindow.hpp"

// #define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
// #include <cmath>

#include "../include/helper.hpp"
#include "../include/shadersource.hpp"
#include "../include/shader.hpp"
// #include "../include/stb_image.hpp"
#include "../include/camera.hpp"
#include "../include/model.hpp"

#include "../include/cube.hpp"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = helper.getScreen_width();
const unsigned int SCR_HEIGHT = helper.getScreen_height();

// camera
Camera camera(glm::vec3(0.0f, 1.0f, 0.0f));
float lastX = helper.getScreen_width() / 2.0f;
float lastY = helper.getScreen_height() / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


myGLwindow::myGLwindow(const char *title, int width, int height)
{
    helper.log(3, "myGLwindow constructor");

    initWindow(title, width, height);
}

int myGLwindow::initWindow(const char* title, int width, int height)
{
    // Initialize GL window
    // Render loop should be managed by a threaded manager
    // #### ---------------------------------------------------------------------------------
    // ####
    // ####
    // ####
    // ####
    // ####
    // ####
    helper.log(3, "initWindow(...)");
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    helper.log(3, "creating window...");
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        helper.log(1, "Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // This is the end of window initial set up. The following is extra to the window
    // #### ---------------------------------------------------------------------------------
    // ####
    // ####
    // ####
    // ####
    // ####
    // ####
    // build and compile our shader zprogram
    // --------------------------------------------------------------------------------------
    helper.log(3, "making shaders...");
    Shader ourShader(helper.vertex_shader_path, helper.fragment_shader_path);
    //Shader modelShader(helper.model_vertex_shader_path, helper.model_fragment_shader_path);

    // load cubes
    Cube* cube = new Cube(0, "", ourShader);

    // load models
    // -----------
    // Model ourModel("../res/objects/backpack/backpack.obj");


    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // world space positions of our cubes
    // Basicaly this is a list of all objects
    // in the world, or at least this is just a list of objects,
    // there may be more than one list.
    glm::vec3 cubePositions[] = {
        // row 1
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 1.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  0.0f,  0.0f),
        glm::vec3( 3.0f,  0.0f,  0.0f),
        // row 2
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3( 1.0f,  0.0f,  1.0f),
        glm::vec3( 2.0f,  0.0f,  1.0f),
        glm::vec3( 3.0f,  0.0f,  1.0f),
        // row 3
        glm::vec3( 0.0f,  0.0f,  2.0f),
        glm::vec3( 1.0f,  0.0f,  2.0f),
        glm::vec3( 2.0f,  0.0f,  2.0f),
        glm::vec3( 3.0f,  0.0f,  2.0f),
        // row 4
        glm::vec3( 0.0f,  0.0f,  3.0f),
        glm::vec3( 1.0f,  0.0f,  3.0f),
        glm::vec3( 2.0f,  0.0f,  3.0f),
        glm::vec3( 3.0f,  0.0f,  3.0f)
    };
    int numCubes = std::size(cubePositions);

    helper.log(3, "entering render loop------");
    // render loop
    // -----------
    int logLevel = 4;
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // Bind textures
        cube->bindTextures();

        // activate shader
        helper.log(logLevel, "activating shader...");
        ourShader.use();

        // camera stuff
        // ------------------------------------------------
        helper.log(logLevel, "projection matrix step 1");
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)helper.getScreen_width() / (float)helper.getScreen_height(), 0.1f, 100.0f);
        helper.log(logLevel, "projection matrix step 2");
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        // ---------------------------------------------------

        // render the loaded model
        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        // model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        //modelShader.setMat4("model", model);
        // ourModel.Draw(ourShader);


        // render
        // ------
        cube->render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        helper.log(logLevel, "swap buffers...");
        glfwSwapBuffers(window);
        glfwPollEvents();

        helper.log(4, std::string("Frame time: " + std::to_string(deltaTime)));
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void myGLwindow::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
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
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
