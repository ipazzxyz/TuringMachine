qt_add_executable(turingmachine
    main.cpp
    main.qrc
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(turingmachine PRIVATE
    turingmachinelogic
    Qt6::Widgets
)

set_target_properties(turingmachine PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
