cmake_minimum_required(VERSION 3.16)
project(open-pos-client VERSION 0.1.0 DESCRIPTION "Aplicativo de gestão de PDV")

configure_file(src/cmake/config.h.in config.h)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})
qt5_add_resources(QT_RESOURCES src/resources/openposclient.qrc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(config src/cpp/config/ConfigController)
target_link_libraries(config PRIVATE Qt5::Widgets)
target_include_directories(config PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_library(mainwindow src/cpp/ui/MainWindow)
target_link_libraries(mainwindow PRIVATE Qt5::Widgets)

add_executable(openpos src/cpp/main.cpp ${QT_RESOURCES})
target_link_libraries(openpos Qt5::Widgets config mainwindow)
target_include_directories(openpos PRIVATE ${CMAKE_CURRENT_BINARY_DIR})