cmake_minimum_required(VERSION 3.16)

project(simpleCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect the platform and configure accordingly.
if(WIN32)
    message(STATUS "Configuring for Windows with vcpkg")

    # Define vcpkg root (adjust this if your installation is elsewhere)
    set(VCPKG_ROOT "C:/vcpkg/installed/x64-windows")

    # Specify include and library directories for vcpkg dependencies
    set(Boost_INCLUDE_DIR "${VCPKG_ROOT}/include")
    set(Boost_LIBRARY_DIR "${VCPKG_ROOT}/lib")
    set(VCPKG_INCLUDE_DIR "${VCPKG_ROOT}/include")
    set(VCPKG_LIB_DIR "${VCPKG_ROOT}/lib")

    # Set directories for glfw3 and GLEW configuration files
    set(glfw3_DIR "${VCPKG_ROOT}/share/glfw3")
    set(GLEW_DIR "${VCPKG_ROOT}/share/glew")

    # Find packages using the vcpkg config files
    find_package(glfw3 CONFIG REQUIRED)
    find_package(GLEW CONFIG REQUIRED)
else()
    message(STATUS "Configuring for Linux (using system libraries)")

    # On Linux, assume the packages are installed via your distribution’s package manager.
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)

    # (Optionally, you can specify Boost paths here if needed. Most Linux systems find Boost automatically.)
    # set(Boost_INCLUDE_DIR "/usr/include")
    # set(Boost_LIBRARY_DIR "/usr/lib")
endif()

# Find OpenGL and Boost (both platforms)
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)

# Create the executable with your source files
add_executable(simpleCPP
    src/main.cpp
    include/helper.hpp
    include/mywindowmanager.hpp
    src/mywindowmanager.cpp
)

# Set include directories.
# On Windows the vcpkg paths are added; on Linux these variables will be empty/unset.
target_include_directories(simpleCPP PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIR}
    ${VCPKG_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${glfw3_INCLUDE_DIRS}
)

# On Windows, explicitly add the library directories from vcpkg
if(WIN32)
    target_link_directories(simpleCPP PRIVATE
        ${Boost_LIBRARY_DIR}
        ${VCPKG_LIB_DIR}
    )
endif()

# Link the libraries (both platforms)
target_link_libraries(simpleCPP PRIVATE
    OpenGL::GL
    glfw
    GLEW::GLEW
    ${Boost_LIBRARIES}
)

# Installation settings
include(GNUInstallDirs)
install(TARGETS simpleCPP
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
