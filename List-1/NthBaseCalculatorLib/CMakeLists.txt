project(NthBaseCalculator)

include_directories(headers)

set(SOURCE_FILES
        src/NthBaseManip.cpp
        src/NthBaseMath.cpp
        src/NthBaseNumber.cpp
        src/UBaseCoder.cpp
)

add_library(NthBaseCalculatorLib STATIC ${SOURCE_FILES})