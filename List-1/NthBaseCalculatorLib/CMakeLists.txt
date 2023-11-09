project(NthBaseCalculator)

include_directories(headers)

set(SOURCE_FILES
        src/NthBaseNumber.cpp
        src/UBaseCoder.cpp
)

add_library(NthBaseCalculatorLib STATIC ${SOURCE_FILES})