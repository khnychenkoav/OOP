#!/bin/bash

echo "Cleaning build directory..."
rm -rf build_int

echo "Creating build directory..."
mkdir build_int

echo "Navigating to build_int directory..."
cd build_int || { echo "Failed to navigate to build_int"; exit 1; }

echo "Configuring with CMake..."
emcmake cmake -DCMAKE_CXX_FLAGS="--bind -std=c++17" -DCMAKE_EXE_LINKER_FLAGS="--bind" ..

echo "Building the project with make..."
emmake make

echo "Copying generated files to src directory..."
cp bin/Allocators.js ../src/Allocators.js
cp bin/Allocators.wasm ../src/Allocators.wasm

echo "Starting server..."
emrun --no_browser --port 8080 ../src/interface.html

echo "Server is running on http://localhost:8080"
