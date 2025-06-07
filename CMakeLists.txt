cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0054 NEW) # Suppress warnings about compatibility with CMake < 3.5

# Set the compilers before the project() command
set(CMAKE_C_COMPILER "/usr/bin/clang-20")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-20")

# Patch glm CMakeLists.txt
file(WRITE ${CMAKE_BINARY_DIR}/_deps/glm-src/CMakeLists.txt "
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
cmake_policy(VERSION 3.16)

set(GLM_VERSION \"0.9.9\")
project(glm VERSION \${GLM_VERSION} LANGUAGES CXX)
enable_testing()

add_subdirectory(glm)
add_library(glm::glm ALIAS glm)

if(\${CMAKE_SOURCE_DIR} STREQUAL \${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(test)
endif()
")

project(OpenGLgame LANGUAGES CXX)

# Set C++20 as the standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
    find_package(assimp REQUIRED)

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

# Collect all source and header files recursively
file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

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
    glm::glm
    assimp
    -lGL
    -lX11
    -lpthread
    -lXrandr
    -lXi
    -ldl
)

# Copy config.text to the build directory
if(EXISTS ${CMAKE_SOURCE_DIR}/config.text)
    configure_file(${CMAKE_SOURCE_DIR}/config.text ${CMAKE_BINARY_DIR}/config.text COPYONLY)
else()
    message(WARNING "config.text not found. Skipping configuration.")
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS ${PROGRAM_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
