#include "../include/cube.hpp"
#include "../include/helper.hpp"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


glm::mat4 Cube::getCube_model()
{
    return cube_model;
}

void Cube::setCube_model(glm::mat4 &newCube_model)
{
    cube_model = newCube_model;
}

glm::vec3 Cube::getPos()
{
    return glm::vec3(0,0,0);
}


Cube::Cube()
    : cube_ID(0),
    cube_str("DEFAULT"),
    cube_model(glm::mat4(1.0f)),
    cube_angle(0.0f),
    position(new glm::vec3(0.0f))
{
    helper.log(3, "Default cube created");
    blockType = BlockType::BlockTypes::EMPTY;
}

Cube::Cube(const int ID, const char* str, glm::mat4 model, float angle, glm::vec3 *pos)
    : cube_ID(ID),
    cube_str(str),
    cube_model(model),
    cube_angle(angle),
    position(pos)
{
    helper.log(3, "Hello from cube");
    blockType = BlockType::BlockTypes::EMPTY;
}


void Cube::render()
{
    // local scope log level
    int logLevel = 4;
    helper.log(logLevel, "render boxes...");
}

void Cube::translate(glm::mat3 translation)
{
    //cube_model = glm::translate(cube_model, translation);
}
