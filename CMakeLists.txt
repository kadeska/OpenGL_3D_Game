cmake_minimum_required(VERSION 3.16)

project(simpleCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify vcpkg paths
set(Boost_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include")
set(Boost_LIBRARY_DIR "C:/vcpkg/installed/x64-windows/lib")
set(VCPKG_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include")
set(VCPKG_LIB_DIR "C:/vcpkg/installed/x64-windows/lib")

# Set glfw3_DIR to point to the location of glfw3Config.cmake
set(glfw3_DIR "C:/vcpkg/installed/x64-windows/share/glfw3")

# Set GLEW_DIR to point to the location of GLEWConfig.cmake
set(GLEW_DIR "C:/vcpkg/installed/x64-windows/share/glew")

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)

# Create the executable
add_executable(simpleCPP
    src/main.cpp
    include/helper.hpp
    include/mywindowmanager.hpp
    src/mywindowmanager.cpp
)

# Include directories (internal + external)
target_include_directories(simpleCPP PRIVATE
    ${Boost_INCLUDE_DIR}  # Boost include path from vcpkg
    ${VCPKG_INCLUDE_DIR}  # General vcpkg include path
    ${OPENGL_INCLUDE_DIRS}  # OpenGL include path
    ${GLEW_INCLUDE_DIRS}  # GLEW include path
    ${glfw3_INCLUDE_DIRS}  # GLFW include path
    ${CMAKE_SOURCE_DIR}/include  # Internal project headers
)

# Link directories (external libraries)
target_link_directories(simpleCPP PRIVATE
    ${Boost_LIBRARY_DIR}  # Boost library path from vcpkg
    ${VCPKG_LIB_DIR}  # General vcpkg lib path
)

# Link required libraries
target_link_libraries(simpleCPP PRIVATE
    OpenGL::GL
    glfw
    GLEW::GLEW
    ${Boost_LIBRARIES}  # Link Boost system & filesystem
)

# Installation paths
include(GNUInstallDirs)
install(TARGETS simpleCPP
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
