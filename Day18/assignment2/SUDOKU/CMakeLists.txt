# Set minimum cmake version
cmake_minimum_required(VERSION 3.16.3)

# Set the project name and version
project(SudokuSolver VERSION 1.0)

# Directory path for .h files
include_directories(include)

# Add executable, i.e. .cpp files
add_executable(SudokuSolver main.cpp src/possible.cpp src/grid.cpp)

