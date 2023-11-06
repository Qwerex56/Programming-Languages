# 'GoogleTests' is the subproject name
project(GoogleTests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
        Google_Tests_run
        UBaseCoderTest.cpp
        NthBaseNumberTest.cpp
)
target_link_libraries(Google_Tests_run NthBaseCalculatorLib)
target_link_libraries(Google_Tests_run gtest gtest_main)