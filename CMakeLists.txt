cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Quick Sql Widgets)

qt_standard_project_setup(REQUIRES 6.8)

include_directories(inc)

add_executable(appInventurverwaltung
    src/main.cpp
    inc/mainwindow.h
    src/mainwindow.cpp
    ui/mainwindow.ui
    ui/Icons.qrc
    src/cmanager_inventurverwaltung.cpp
    inc/cmanager_inventurverwaltung.h
    inc/cdia_anmelden.h
    src/cdia_anmelden.cpp
    ui/cdia_anmelden.ui
    inc/cmyapplication.h
    src/cmyapplication.cpp

    src/cdia_neuanlage.cpp
    inc/cdia_neuanlage.h
    ui/cdia_neuanlage.ui

    src/filterproxymodel.cpp
    inc/filterproxymodel.h
)

target_link_libraries(appInventurverwaltung
    PRIVATE Qt6::Quick
    Qt6::Widgets
)
target_link_libraries(appInventurverwaltung PRIVATE Qt6::Sql Qt6::Quick Qt6::Widgets)
