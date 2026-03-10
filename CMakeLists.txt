cmake_minimum_required(VERSION 3.31)
project(PathFinder)

set(CMAKE_CXX_STANDARD 20)

add_executable(PathFinder main.cpp
        PathFinder.h
        PathFinder.cpp)
