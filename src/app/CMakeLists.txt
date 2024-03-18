add_executable(TuringMachine
    main.cpp
    main.qrc
    MainWindow.ui
    MainWindow.cpp
    MainWindow.hpp
)
target_link_libraries(TuringMachine PRIVATE
    TM
    Qt5::Widgets
)
set_target_properties(TuringMachine PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)