cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        untitled
        Processing_Tree.cpp
        Similarity.cpp
        Similarity.h
        main.cpp
        HashFunc.cpp
        HashFunc.h
)
