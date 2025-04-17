#pragma once

#include "shader.hpp"
#include "worldManager.hpp"

class RenderManager
{
public:
    /**
     * @brief RenderManager constructor
     */
    RenderManager(Shader* shader);

    /**
     * @brief RenderManager destructor
     */
    ~RenderManager();

    /**
     * @brief Render the scene
     * This function renders the scene using the shader program.
     * It binds the textures and draws the world. 
     */
    // void renderScene();

    /**
     * @brief Render the scene with a world
     * This function renders the scene using the shader program.
     * It binds the textures and draws the world. 
     * @param world The world to render
     */
    void renderScene(World* world);

    /**
     * @brief Initialize the render manager
     * This function initializes the render manager.
     * It sets up the vertex buffer object (VBO) and vertex array object (VAO).
     */
    void init();

    /**
     * @brief Update the shader program
     * This function updates the shader program.
     * It sets the view and projection matrices.
     * @param world The world to use for updating the shader
     */
    void updateShader(World* world);

    /**
     * @brief Bind the textures
     * This function binds the textures for rendering.
     */
    void bindTextures();

    /**
     * @brief Get the current world being used
     * @return The current world being used
     */
    World* getCurrentWorld();

private:
    /**
     * @brief The shader program that will be used thruout the program.
     */
    Shader* current_shader;

    /**
     * @brief The world to be used for rendering.
     */
    World* world;

    /**
     * @brief The texture IDs for the cube textures.
     */
    unsigned int cube_texture1, cube_texture2;
    
    /**
     * @brief The vertex buffer object (VBO) and vertex array object (VAO) for the cube.
     */
    unsigned int cube_VBO, cube_VAO;

};
