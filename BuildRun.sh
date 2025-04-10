#!/bin/bash
# filepath: /home/jh/Dev/CPP/OpenGL/OpenGL_3D_Game/build_and_run.sh

# Navigate to the build directory
BUILD_DIR="../build"
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi
cd "$BUILD_DIR"

# Run CMake to configure the project
echo "Configuring the project with CMake..."
cmake ../OpenGL_3D_Game

# Build the project
echo "Building the project..."
cmake --build . -- -j$(nproc)

# Check if the executable exists
EXECUTABLE="./OpenGLgame"
if [ -f "$EXECUTABLE" ]; then
    echo "Build successful. Running the program..."
    $EXECUTABLE
else
    echo "Build failed or executable not found."
fi