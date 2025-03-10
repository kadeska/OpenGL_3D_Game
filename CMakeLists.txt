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
    set(Qt6_DIR "${VCPKG_ROOT}/share/qt6")  # Adjust for Qt5 if needed

    # Find packages using the vcpkg config files (CONFIG mode)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(GLEW CONFIG REQUIRED)
    find_package(assimp CONFIG REQUIRED)
    find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets)  # Use Qt5 if necessary
else()
    message(STATUS "Configuring for Linux (using system libraries)")

    # Assume system-installed packages; ensure required development packages are installed.
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(assimp REQUIRED)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)  # Adjust for Qt5 if necessary

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

# Recursively search for all .cpp and .hpp files in the src and include directories.
file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

# --- Ensure MOC Processing for Qt Headers ---
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# --- Define the Executable ---
add_executable(simpleCPP ${PROJECT_SOURCES})

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
    Qt6::Widgets  # Adjust to Qt5::Widgets if necessary
)

# --- Installation Settings ---
include(GNUInstallDirs)
install(TARGETS simpleCPP
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
