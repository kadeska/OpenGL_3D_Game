#!/bin/bash
# filepath: /home/jh/Dev/CPP/OpenGL/OpenGL_3D_Game/BuildRun.sh

# Navigate to the build directory
BUILD_DIR="../build"
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi
cd "$BUILD_DIR"

# Use ccache for faster builds
export CC="ccache gcc"
export CXX="ccache g++"

# Run CMake to configure the project (only if necessary)
if [ ! -f "CMakeCache.txt" ]; then
    echo "Configuring the project with CMake..."
    cmake -G Ninja ../OpenGL_3D_Game
    if [ $? -ne 0 ]; then
        echo "CMake configuration failed. Exiting."
        exit 1
    fi
else
    echo "CMake configuration already exists. Skipping configuration step."
fi

# Build the project
echo "Building the project..."
cmake --build . -- -j$(nproc)
if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

# Check if the executable exists
EXECUTABLE="./OpenGLgame"
if [ -f "$EXECUTABLE" ]; then
    echo "Build successful. Running the program..."
    $EXECUTABLE
else
    echo "Build failed or executable not found."
fi