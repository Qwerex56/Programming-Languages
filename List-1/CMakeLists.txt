cmake_minimum_required(VERSION 3.26)
project(List_1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

add_executable(
        List_1 main.cpp
#        src/BinaryCoder.cpp
#        src/BinaryCoder.h
#        src/NthBaseNumber.cpp
        headers/NthBaseNumber.h
#        src/DecimalCoder.cpp
        headers/DecimalCoder.h
        headers/NumberCoder.h
)
