#pragma once

#include "shader.hpp"

class RenderManager
{
public:
    RenderManager(Shader* shader);
    void renderScene();
    void init();
    void bindTextures();

private:
    Shader* myShader;
    unsigned int cube_texture1, cube_texture2;
    unsigned int cube_VBO, cube_VAO;
};
