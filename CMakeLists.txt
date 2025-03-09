cmake_minimum_required(VERSION 3.16)

project(simpleCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Platform-Specific Configuration ---
if(WIN32)
    message(STATUS "Configuring for Windows (using vcpkg)")
    cmake_policy(SET CMP0144 NEW)

    # Define vcpkg root (adjust if needed)
    set(VCPKG_ROOT "C:/vcpkg/installed/x64-windows")

    # Tell CMake where to find Boost (vcpkg installation)
    set(BOOST_ROOT "${VCPKG_ROOT}")
    set(BOOST_INCLUDEDIR "${VCPKG_ROOT}/include")
    set(BOOST_LIBRARYDIR "${VCPKG_ROOT}/lib")

    # Specify where to find the package configuration files
    set(glfw3_DIR "${VCPKG_ROOT}/share/glfw3")
    set(GLEW_DIR "${VCPKG_ROOT}/share/glew")
    set(assimp_DIR "${VCPKG_ROOT}/share/assimp")

    # Find packages using the vcpkg config files (CONFIG mode)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(GLEW CONFIG REQUIRED)
    find_package(assimp CONFIG REQUIRED)
else()
    message(STATUS "Configuring for Linux (using system libraries)")

    # Assume system-installed packages; ensure required development packages are installed.
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(assimp REQUIRED)

    include(FetchContent)
    FetchContent_Declare(
      glad
      GIT_REPOSITORY https://github.com/Dav1dde/glad.git
      GIT_TAG        v0.1.36  # You can choose a specific release tag
    )

    FetchContent_MakeAvailable(glad)
endif()

# Find common packages on both platforms.
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)

# --- Define the Executable ---
add_executable(simpleCPP
    src/main.cpp
    include/helper.hpp
    include/mywindowmanager.hpp
    src/mywindowmanager.cpp
    src/mycore.cpp
    include/mycore.hpp
    src/mycore.cpp
    src/filemanager.cpp
    include/filemanager.hpp
    include/myglwindow.hpp src/gl/window/myglwindow.cpp
    include/shadersource.hpp
    include/shader.hpp
    include/std_image.hpp
    include/shaders/vertex.shader
    include/shaders/fragment.shader
    include/camera.hpp
    include/shader_m.hpp
)

# Include your project's own headers.
target_include_directories(simpleCPP PRIVATE ${CMAKE_SOURCE_DIR}/include)

# --- Determine the Correct GLFW Target ---
if(TARGET glfw3::glfw3)
    set(GLFW_TARGET glfw3::glfw3)
elseif(TARGET glfw)
    set(GLFW_TARGET glfw)
else()
    message(FATAL_ERROR "No suitable GLFW target found. Make sure GLFW is installed correctly.")
endif()

# --- Link Libraries ---
target_link_libraries(simpleCPP PRIVATE
    OpenGL::GL
    ${GLFW_TARGET}
    GLEW::GLEW
    glad
    ${Boost_LIBRARIES}
    assimp::assimp
)

# --- Installation Settings ---
include(GNUInstallDirs)
install(TARGETS simpleCPP
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
