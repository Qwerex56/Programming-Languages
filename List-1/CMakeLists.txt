cmake_minimum_required(VERSION 3.26)
project(List_1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

add_executable(
        List_1 main.cpp
        src/NthBaseNumber.cpp
        headers/NthBaseNumber.h
        headers/UBaseCoder.h
        Interfaces/NumberCoder.h
)

add_subdirectory(Tests/GoogleTests)