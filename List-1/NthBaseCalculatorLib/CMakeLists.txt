project(NthBaseCalculator)

include_directories(headers)

set(SOURCE_FILES
        src/NthBaseNumber.cpp
        src/UBaseCoder.cpp
        src/NthBaseMath.cpp
        src/NthBaseManip.cpp
)

add_library(NthBaseCalculatorLib STATIC ${SOURCE_FILES})