cmake_minimum_required(VERSION 3.10)
project(OpenGLExample3D)

set(CMAKE_CXX_STANDARD 17)

add_executable(OpenGLExample3D
    src/main.cpp
    src/filemanager.cpp
    include/glad/glad.c
    src/world.cpp
)

cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

find_path(GLM_INCLUDE_DIR glm/glm.hpp)
if(GLM_INCLUDE_DIR)
    target_include_directories(OpenGLExample3D PRIVATE ${GLM_INCLUDE_DIR})
endif()

# Use the project root as an include directory so glad/glad.h is found
target_include_directories(OpenGLExample3D PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(OpenGLExample3D PRIVATE OpenGL::GL glfw)

# --- Copy shader files to build directory ---
add_custom_command(
    TARGET OpenGLExample3D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/shader.vs
        $<TARGET_FILE_DIR:OpenGLExample3D>/shader.vs
)
add_custom_command(
    TARGET OpenGLExample3D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/shader.fs
        $<TARGET_FILE_DIR:OpenGLExample3D>/shader.fs
)
add_custom_command(
    TARGET OpenGLExample3D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/game_config.txt
        $<TARGET_FILE_DIR:OpenGLExample3D>/game_config.txt
)