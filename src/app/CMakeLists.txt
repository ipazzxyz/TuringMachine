add_executable(TuringMachine
    main.cpp
    main.qrc
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
)
target_link_libraries(TuringMachine PRIVATE
    TM
    Qt5::Widgets
)
set_target_properties(TuringMachine PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)