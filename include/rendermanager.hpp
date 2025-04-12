#pragma once

#include "shader.hpp"
#include "worldManager.hpp"

class RenderManager
{
public:
    RenderManager(Shader* shader);
    ~RenderManager();
    void renderScene();
    void renderScene(World world);
    void init();
    void bindTextures();

private:
    Shader* myShader;
    unsigned int cube_texture1, cube_texture2;
    unsigned int cube_VBO, cube_VAO;
    WorldManager worldManager = WorldManager();

};
