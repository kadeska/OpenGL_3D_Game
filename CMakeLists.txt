cmake_minimum_required(VERSION 3.16)

project(OpenGLgame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the program name
set(PROGRAM_NAME OpenGLgame)

# --- Platform-Specific Configuration ---
if(WIN32)
    message(STATUS "Configuring for Windows (using vcpkg)")
    cmake_policy(SET CMP0144 NEW)

    set(VCPKG_ROOT "C:/vcpkg/installed/x64-windows")
    set(BOOST_ROOT "${VCPKG_ROOT}")
    set(BOOST_INCLUDEDIR "${VCPKG_ROOT}/include")
    set(BOOST_LIBRARYDIR "${VCPKG_ROOT}/lib")

    set(glfw3_DIR "${VCPKG_ROOT}/share/glfw3")
    set(GLEW_DIR "${VCPKG_ROOT}/share/glew")
    set(assimp_DIR "${VCPKG_ROOT}/share/assimp")
    set(Qt6_DIR "${VCPKG_ROOT}/share/qt6")

    find_package(glfw3 CONFIG REQUIRED)
    find_package(GLEW CONFIG REQUIRED)
    find_package(assimp CONFIG REQUIRED)
    find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets)
else()
    message(STATUS "Configuring for Linux (using system libraries)")

    # Ensure dependencies are installed
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)

    include(FetchContent)

    # Fetch glad
    FetchContent_Declare(
      glad
      GIT_REPOSITORY https://github.com/Dav1dde/glad.git
      GIT_TAG        v0.1.36
    )
    FetchContent_MakeAvailable(glad)

    # Fetch glm
    FetchContent_Declare(
      glm
      GIT_REPOSITORY https://github.com/g-truc/glm.git
      GIT_TAG        0.9.9.8
    )
    FetchContent_MakeAvailable(glm)
endif()

file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Define the Executable
add_executable(${PROGRAM_NAME} ${PROJECT_SOURCES})

# Include directories
target_include_directories(${PROGRAM_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Determine GLFW Target
if(TARGET glfw3::glfw3)
    set(GLFW_TARGET glfw3::glfw3)
elseif(TARGET glfw)
    set(GLFW_TARGET glfw)
else()
    message(FATAL_ERROR "No suitable GLFW target found. Make sure GLFW is installed correctly.")
endif()

# Link Libraries
target_link_libraries(${PROGRAM_NAME} PRIVATE
    OpenGL::GL
    ${GLFW_TARGET}
    GLEW::GLEW
    glad
    glm
)

# Copy config.text to the build directory
configure_file(${CMAKE_SOURCE_DIR}/config.text ${CMAKE_BINARY_DIR}/config.text COPYONLY)

# Installation
include(GNUInstallDirs)
install(TARGETS ${PROGRAM_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
