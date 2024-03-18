add_library(TM STATIC
    Exception.hpp
    Function.hpp
    TuringMachine.cpp
    TuringMachine.hpp
)
target_include_directories(TM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})