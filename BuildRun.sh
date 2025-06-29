#!/bin/bash

# Function to detect the package manager and install dependencies
install_dependencies() {
    echo "Checking and installing dependencies..."

    if command -v apt-get &> /dev/null; then
        sudo apt-get update
        sudo apt-get install -y build-essential cmake ninja-build libgl1-mesa-dev libglew-dev libglfw3-dev clang-20
    elif command -v dnf &> /dev/null; then
        sudo dnf install -y gcc gcc-c++ cmake ninja-build mesa-libGL-devel glew-devel glfw-devel clang
    elif command -v pacman &> /dev/null; then
        sudo pacman -Syu --noconfirm base-devel cmake ninja mesa glew glfw clang
    elif command -v zypper &> /dev/null; then
        sudo zypper install -y gcc gcc-c++ cmake ninja mesa-libGL-devel glew-devel glfw-devel clang
    else
        echo "Unsupported package manager. Please install dependencies manually."
        exit 1
    fi
}

# Install dependencies
install_dependencies

# Navigate to the build directory
BUILD_DIR="../build"
if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning the build directory..."
    rm -rf "$BUILD_DIR"
fi
mkdir "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure the project
echo "Configuring the project with CMake..."
cmake -G "Ninja" -DCMAKE_C_COMPILER=/usr/bin/clang-20 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-20 -DCMAKE_CXX_STANDARD=20 ../OpenGLExample3D
if [ $? -ne 0 ]; then
    echo "CMake configuration failed. Exiting."
    exit 1
fi

# Build the project
echo "Building the project..."
cmake --build . -- -j$(nproc)
if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

# Run the executable
EXECUTABLE="./OpenGLExample3D"
if [ -f "$EXECUTABLE" ]; then
    echo "Build successful. Running the program..."
    $EXECUTABLE
else
    echo "Build failed or executable not found."
fi