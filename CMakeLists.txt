cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Sql Widgets)

qt_standard_project_setup(REQUIRES 6.8)

add_executable(appInventurverwaltung
    main.cpp
    cmanager_inventurverwaltung.cpp
    cmanager_inventurverwaltung.h
)


target_link_libraries(appInventurverwaltung
    PRIVATE Qt6::Quick
    Qt6::Sql
    Qt6::Widgets
)
