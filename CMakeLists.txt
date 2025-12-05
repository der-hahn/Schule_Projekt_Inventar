cmake_minimum_required(VERSION 3.16)

project(Inventurverwaltung VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)

qt_standard_project_setup(REQUIRES 6.8)

add_executable(appInventurverwaltung
    main.cpp
    mainwindow.h mainwindow.cpp mainwindow.ui
    Icons.qrc
)

target_link_libraries(appInventurverwaltung
    PRIVATE Qt6::Quick
    Qt6::Widgets
)
target_link_libraries(appInventurverwaltung PRIVATE Qt6::Sql)
