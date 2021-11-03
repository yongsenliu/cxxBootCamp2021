cmake_minimum_required(VERSION 3.5.1)
project(testCmake)
include_directories(include)
add_executable(testCmake source/a.cpp source/b.cpp main.cpp)
