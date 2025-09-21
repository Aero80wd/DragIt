cmake_minimum_required(VERSION 3.31)
project(DragIt)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QRC_SOURCE_FILE res.qrc)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

add_executable(DragIt main.cpp
        MainWindow.cpp
        MainWindow.h
        DragWidget.cpp
        DragWidget.h
res.qrc
icon.rc)
target_link_libraries(DragIt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
)

