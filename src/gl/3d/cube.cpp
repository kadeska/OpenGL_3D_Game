#include "../include/cube.hpp"
#include "../include/helper.hpp"





Cube::Cube(const int* ID, const char* str)
    : cube_ID(ID),
    cube_str(str)
{
    helper.log(3, "Hello from cube");
}


void Cube::render()
{
    // local scope log level
    int logLevel = 4;
    helper.log(logLevel, "render boxes...");
}
