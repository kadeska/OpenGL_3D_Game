#!/bin/bash

# Function to detect the package manager and install dependencies
install_dependencies() {
    echo "Checking and installing dependencies..."

    if command -v apt-get &> /dev/null; then
        # Debian/Ubuntu-based distributions
        sudo apt-get update
        sudo apt-get install -y build-essential cmake ninja-build libgl1-mesa-dev libglew-dev libglfw3-dev
    elif command -v dnf &> /dev/null; then
        # Fedora-based distributions
        sudo dnf install -y gcc gcc-c++ cmake ninja-build mesa-libGL-devel glew-devel glfw-devel
    elif command -v pacman &> /dev/null; then
        # Arch-based distributions
        sudo pacman -Syu --noconfirm base-devel cmake ninja mesa glew glfw
    elif command -v zypper &> /dev/null; then
        # openSUSE-based distributions
        sudo zypper install -y gcc gcc-c++ cmake ninja mesa-libGL-devel glew-devel glfw-devel
    else
        echo "Unsupported package manager. Please install the following dependencies manually:"
        echo " - build-essential (or equivalent)"
        echo " - cmake"
        echo " - ninja-build"
        echo " - OpenGL development libraries"
        echo " - GLEW development libraries"
        echo " - GLFW development libraries"
        exit 1
    fi
}

# Install dependencies
install_dependencies

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