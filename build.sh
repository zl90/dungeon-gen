#!/bin/bash

# This script will build and run the program.

# Create a build directory if it doesn't exist and change to that directory
mkdir -p build && cd build

# Run CMake to generate build files
cmake ..

# Build the project using the generated build files
cmake --build .

# Run the DungeonGenerator executable
./DungeonGenerator
