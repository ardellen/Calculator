cmake_minimum_required(VERSION 3.5)

project(Calc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS PrintSupport Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ../s21_calculation.cc
        ../s21_calculation.h
        ../s21_controller.h
        ../s21_controller.cc
        ../s21_map.cc
        ../s21_map.h
        ../s21_parser.cc
        ../s21_parser.h
        ../s21_model.cc
        ../s21_model.h
        ../s21_token.h
        ../s21_token.cc
        ../s21_validator.h
        ../s21_validator.cc
        ../s21_polish_notation.h
        ../s21_polish_notation.cc
        ../s21_helpers.cc
        ../s21_helpers.h
        qcustomplot.cpp
        qcustomplot.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Calc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Calc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Calc SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Calc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Calc PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)


set_target_properties(Calc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Calc)
endif()
