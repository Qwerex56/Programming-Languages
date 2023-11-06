project(NthBaseCalculator)

include_directories(headers)

set(SOURCE_FILES
        src/NthBaseNumber.cpp
)

add_library(NthBaseCalculatorLib STATIC ${SOURCE_FILES})