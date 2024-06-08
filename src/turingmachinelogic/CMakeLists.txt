qt_add_library(turingmachinelogic STATIC
    exception.h
    function.h
    turingmachine.cpp
    turingmachine.h
)
target_link_libraries(turingmachinelogic PRIVATE Qt6::Core)
target_include_directories(turingmachinelogic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})