#!/bin/bash

echo "Checking for required dependencies..."

# Detect package manager (APT for Debian/Ubuntu, DNF for Fedora)
if command -v apt >/dev/null; then
    PKG_MANAGER="apt"
    INSTALL_CMD="sudo apt install -y"
elif command -v dnf >/dev/null; then
    PKG_MANAGER="dnf"
    INSTALL_CMD="sudo dnf install -y"
else
    echo "Unsupported Linux distribution. Please install dependencies manually."
    exit 1
fi

# List of required packages
DEPENDENCIES=("libglfw3-dev" "libglew-dev" "libboost-all-dev")

for package in "${DEPENDENCIES[@]}"; do
    if dpkg -s $package &>/dev/null || rpm -q $package &>/dev/null; then
        echo "$package is already installed."
    else
        echo "Installing $package..."
        $INSTALL_CMD $package
    fi
done

echo "All dependencies are installed."
