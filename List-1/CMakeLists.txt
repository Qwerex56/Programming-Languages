cmake_minimum_required(VERSION 3.26)
project(List_1)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES main.cpp)
add_executable(NthBaseCalculator_run ${SOURCE_FILES})

include_directories(NthBaseCalculatorLib/headers)
add_subdirectory(NthBaseCalculatorLib)

target_link_libraries(NthBaseCalculator_run NthBaseCalculatorLib)

add_subdirectory(Tests/GoogleTests)

#add_executable(
#        List_1 main.cpp
#        src/NthBaseNumber.cpp
#        headers/NthBaseNumber.h
#        headers/UBaseCoder.h
#        headers/NumberCoder.h
#)

