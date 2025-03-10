#include "../include/cube.hpp"
#include "../include/helper.hpp"





Cube::Cube(const int ID, const char* str, glm::mat4 model, float angle)
    : cube_ID(ID),
    cube_str(str),
    cube_model(model),
    cube_angle(angle)
{
    helper.log(3, "Hello from cube");
}


void Cube::render()
{
    // local scope log level
    int logLevel = 4;
    helper.log(logLevel, "render boxes...");
}
