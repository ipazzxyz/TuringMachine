add_library(TM STATIC
    exception.h
    function.h
    turingmachine.cpp
    turingmachine.h
)
target_include_directories(TM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})