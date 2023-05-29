cmake_minimum_required(VERSION 3.16)

project(marine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 COMPONENTS Quick Widgets QuickControls2 Network REQUIRED)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror=return-type -fno-omit-frame-pointer -Wextra")
endif()

qt_add_executable(appmarine
    src/main.cpp
    src/Commandline.h
    src/Commandline.cpp
    src/StyleSettings.h
    src/StyleSettings.cpp
    src/Interface.h
    src/Interface.cpp
    src/SubScribesModel.h
    src/SubScribesModel.cpp
    misc/pictures.qrc
)

# Not Format Me
qt_add_qml_module(appmarine
    URI Marine
    VERSION 1.0
    QML_FILES
        ./qml/Main.qml
        ./qml/ScrollablePage.qml
        ./qml/pages/LinksPage.qml
        ./qml/pages/SubScribePage.qml
        ./qml/pages/SubScribePage/SubScribeDelegate.qml
        ./qml/pages/SubScribePage/OverViewDelegate.qml
)

set_target_properties(appmarine PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appmarine
    PRIVATE
    Qt6::Quick
    Qt6::Widgets
    Qt6::QuickControls2
    Qt6::Network
)

install(TARGETS appmarine
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
