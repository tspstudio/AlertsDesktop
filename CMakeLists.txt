cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)

project(AlertsDesktop)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(NOTIFY REQUIRED libnotify)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Svg SvgWidgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)  # Enables automatic processing of .ui files

add_executable(AlertsDesktop 
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    src/mainwindow.ui
    src/Network.h
    src/Network.cpp
    src/ReadFile.h
    src/ReadFile.cpp
    src/Status.h
    src/Map.h
    src/Map.cpp
)

target_link_libraries(AlertsDesktop PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
    Qt6::Svg
    Qt6::SvgWidgets
)

target_include_directories(AlertsDesktop PRIVATE 
    ${GLIB_INCLUDE_DIRS} 
    ${NOTIFY_INCLUDE_DIRS}
)

target_link_libraries(AlertsDesktop PRIVATE 
    ${GLIB_LIBRARIES} 
    ${NOTIFY_LIBRARIES} 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets 
    Qt6::Svg
    Qt6::SvgWidgets
    curl
)

target_compile_options(AlertsDesktop PRIVATE ${GLIB_CFLAGS_OTHER} ${NOTIFY_CFLAGS_OTHER})