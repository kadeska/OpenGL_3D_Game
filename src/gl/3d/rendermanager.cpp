#include "../include/rendermanager.hpp"
#include "../include/helper.hpp"
#include "cube.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include "../include/stb_image.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <random>

#include <ctime>  // Include this for time()



// Shader* myShader;
// unsigned int cube_texture1, cube_texture2;
// unsigned int cube_VBO, cube_VAO;


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
    glm::vec3( 3.0f,  0.0f,  3.0f),

    glm::vec3( 3.0f,  1.0f,  4.0f)
};
int numCubes = std::size(cubePositions);

// Declare the vector of Cube pointers (stack variable)
std::vector<Cube*> cubeArray;

RenderManager::RenderManager(Shader* shader)
    : myShader(shader)
{
    helper.log(3, "Hello from RenderManager");
    // Dynamically allocate a Cube and push its pointer into the vector
    Cube* cube;// = new Cube(0, "");
    //cubeArray.push_back(cube);
    // calculate the model matrix for each object and pass it to shader before drawing
    for (unsigned int i = 0; i < numCubes; i++){
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[i]);
        float angle = 0.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        //srand(time(0));
        cube = new Cube(i + 1, "cube", model, angle);
        //cube->cube_ID = rand();
        myShader->setMat4("model", model);
        cubeArray.push_back(cube);
    }
    for (size_t i = 0; i < cubeArray.size(); i++) {
        if (cubeArray[i]) {  // Ensure cubeArray[i] is valid
            if (cubeArray[i]->cube_ID) {  // Ensure cube_ID is valid
                helper.log(3, "Cube ID: " + std::to_string(cubeArray[i]->cube_ID));
            } else {
                helper.log(3, "Cube ID is null!");
            }

            if (cubeArray[i]->cube_str) {  // Ensure cube_str is valid
                helper.log(3, "Cube str: " + std::string(cubeArray[i]->cube_str));
            } else {
                helper.log(3, "Cube str is null!");
            }
        }
    }

    init();
}

// Remember to delete allocated Cubes when they are no longer needed.


void RenderManager::renderScene()
{
    bindTextures();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // render boxes
    // for every object/cube
    for (Cube* cube : cubeArray)
    {
        myShader->setMat4("model", cube->cube_model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void RenderManager::init()
{
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

    helper.log(3, "generating beffer data and generating atributes...");
    glGenVertexArrays(1, &cube_VAO);
    glGenBuffers(1, &cube_VBO);

    glBindVertexArray(cube_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    helper.log(3, "loading textures...");
    // load and create a texture
    // -------------------------

    // texture 1
    // ---------
    glGenTextures(1, &cube_texture1);
    glBindTexture(GL_TEXTURE_2D, cube_texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int texture_width, texture_height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("../res/container.jpg", &texture_width, &texture_height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        helper.log(1, "Failed to load texture 1");
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &cube_texture2);
    glBindTexture(GL_TEXTURE_2D, cube_texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("../res/awesomeface.png", &texture_width, &texture_height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        helper.log(1, "Failed to load texture 2");
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    myShader->use();
    myShader->setInt("texture1", 0);
    myShader->setInt("texture2", 1);

    // modelShader.use();
}

void RenderManager::bindTextures()
{
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cube_texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, cube_texture2);

    // bind vertex array
    glBindVertexArray(cube_VAO);
}
RenderManager::~RenderManager() {
    for (Cube* cube : cubeArray) {
        delete cube;
    }
}
