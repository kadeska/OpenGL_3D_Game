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
#include "rendermanager.hpp"



// Shader* myShader;
// unsigned int cube_texture1, cube_texture2;
// unsigned int cube_VBO, cube_VAO;

/**
 * @brief cubePositions
 * List of cube positions
 */
// glm::vec3 cubePositions[] = {
//     // row 1
//     glm::vec3( 0.0f,  0.0f,  0.0f),    // some position in 3d space. Can be repesented by a position object that will store the vec3 position and any relative data for that position, such as is this position occupide by a physical object? if so, what is that data? Point to object data.
//     glm::vec3( 1.0f,  0.0f,  0.0f),
//     glm::vec3( 2.0f,  0.0f,  0.0f),
//     glm::vec3( 3.0f,  0.0f,  0.0f),
//     // row 2
//     glm::vec3( 0.0f,  0.0f,  1.0f),
//     glm::vec3( 1.0f,  0.0f,  1.0f),
//     glm::vec3( 2.0f,  0.0f,  1.0f),
//     glm::vec3( 3.0f,  0.0f,  1.0f),
//     // row 3
//     glm::vec3( 0.0f,  0.0f,  2.0f),
//     glm::vec3( 1.0f,  0.0f,  2.0f),
//     glm::vec3( 2.0f,  0.0f,  2.0f),
//     glm::vec3( 3.0f,  0.0f,  2.0f),
//     // row 4
//     glm::vec3( 0.0f,  0.0f,  3.0f),
//     glm::vec3( 1.0f,  0.0f,  3.0f),
//     glm::vec3( 2.0f,  0.0f,  3.0f),
//     glm::vec3( 3.0f,  0.0f,  3.0f),

//     glm::vec3( 3.0f,  1.0f,  4.0f)
// };
// int numCubes = std::size(cubePositions);

// Declare the vector of Cube pointers (stack variable)
// std::vector<Cube*> cubeArray; // change this to be the world manager
// get the cube array from the world manager


// RenderManager constructor
// This should just generate an empty shader object.
// The cube positions array should be populated by world generator. It should not be in here.
// The world generator should be passed to the render manager to generate the new shader 
// object with the generated world.
RenderManager::RenderManager(Shader* shader) : current_shader(shader)
{
    helper.log(3, "RenderManager constructor");
    current_shader = shader;
    world = nullptr;

    // wait to call this after the world is generated, because 
    // this function generates the buffers.
    // init();
}

// foobar(){
//     // set the matrix and position of each cube.
//     // this needs to be 
//     for (unsigned int i = 0; i < numCubes; i++){
//         glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//         model = glm::translate(model, cubePositions[i]);
//         float angle = 0.0f * i;
//         model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

//         //srand(time(0));
//         cube = new Cube(i + 1, "cube", model, angle, cubePositions[i]);
//         //cube->cube_ID = rand();
//         myShader->setMat4("model", model);
//         cubeArray.push_back(cube);
//     }
//     for (size_t i = 0; i < cubeArray.size(); i++) {
//         if (cubeArray[i]) {  // Ensure cubeArray[i] is valid
//             if (cubeArray[i]->cube_ID) {  // Ensure cube_ID is valid
//                 helper.log(3, "Cube ID: " + std::to_string(cubeArray[i]->cube_ID));
//             } else {
//                 helper.log(3, "Cube ID is null!");
//             }

//             if (cubeArray[i]->cube_str) {  // Ensure cube_str is valid
//                 helper.log(3, "Cube str: " + std::string(cubeArray[i]->cube_str));
//             } else {
//                 helper.log(3, "Cube str is null!");
//             }
//         }
//     }
// }

// Remember to delete allocated Cubes when they are no longer needed.


// void RenderManager::renderScene()
// {
//     bindTextures();
//     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     // render boxes
//     // for every object/cube
//     for (Cube* cube : cubeArray)
//     {
//         myShader->setMat4("model", cube->cube_model);
//         glDrawArrays(GL_TRIANGLES, 0, 36);
//     }

//     // update world and render cubes
//     // WorldGenerator

// }

void RenderManager::renderScene(World* world)
{
    bindTextures();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // world->update();
    // render boxes
    // for every object/cube


    init();

    for (Cube cube : world->getWorld())
    {
        current_shader->setMat4("model", cube.cube_model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // world->update();
    }

    // unsigned int instanceVBO;
    // glGenBuffers(1, &instanceVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    // glBufferData(GL_ARRAY_BUFFER, world->getWorld().size() * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);

    // std::vector<glm::mat4> instanceMatrices;
    // for (Cube& cube : world->getWorld()) {
    //     instanceMatrices.push_back(cube.getCube_model());
    // }
    // glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, instanceMatrices.size() * sizeof(glm::mat4), instanceMatrices.data());


    // glBindVertexArray(cube_VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

    // for (unsigned int i = 0; i < 4; i++) {
    //     glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * sizeof(glm::vec4)));
    //     glEnableVertexAttribArray(3 + i);
    //     glVertexAttribDivisor(3 + i, 1); // Tell OpenGL this is per-instance data
    // }

    // glDrawArraysInstanced(GL_TRIANGLES, 0, 36, world->getWorld().size());


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
    
    // Move to config file
    unsigned char *data = stbi_load("../OpenGL_3D_Game/res/container.jpg", &texture_width, &texture_height, &nrChannels, 0);
    
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
    
    // Move to config file
    data = stbi_load("../OpenGL_3D_Game/res/awesomeface.png", &texture_width, &texture_height, &nrChannels, 0);
    
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
    current_shader->use();
    current_shader->setInt("texture1", 0);
    current_shader->setInt("texture2", 1);

    // modelShader.use();
}

void RenderManager::updateShader(World * world)
{
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
World* RenderManager::getCurrentWorld()
{
    if (world == nullptr)
    {
        helper.log(1, "World is null");
        return nullptr;
    }
    return world;
}
RenderManager::~RenderManager()
{
    // for (Cube* cube : cubeArray) {
    //     delete cube;
    // }
}
