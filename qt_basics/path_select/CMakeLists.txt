cmake_minimum_required(VERSION 3.16)
project(qt_demo)

# includes
include(${CMAKE_CURRENT_LIST_DIR}/QTUtils.cmake)

# configurations
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)

# add QT
if(NOT DEFINED ENV{QT_DIR})
    message(FATAL "Env-var QT_DIR not defined")
endif()
file(TO_CMAKE_PATH "$ENV{QT_DIR}" MS_QT_ROOT)
list(APPEND CMAKE_PREFIX_PATH "${MS_QT_ROOT}")

find_package(QT NAMES Qt5 Qt6 COMPONENTS Core Qml REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Qml Gui Network Quick REQUIRED)

# find QML
file(GLOB_RECURSE _QMLFiles *.qml)
get_dirs_from_paths(_QMLDirs ${_QMLFiles})

# demo
add_executable(qt_demo
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/qml.qrc
    ${_QMLFiles}
)
target_link_libraries(qt_demo
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Qml
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Quick
)
target_compile_definitions(qt_demo
    PRIVATE
        QT_NO_KEYWORDS
)

# # deploy demo: !!! uncomment for the first time of your build
# set(QT_DEPLOY_EXE ${MS_QT_ROOT}/bin/windeployqt.exe)
# set(QT_DEPLOY_COMMAND ${QT_DEPLOY_EXE} --$<LOWER_CASE:$<CONFIG>> $<TARGET_FILE:qt_demo>)
# foreach(_d ${_QMLDirs})
#     list(APPEND QT_DEPLOY_COMMAND --qmldir ${_d})
# endforeach(_d)
# add_custom_command(
#     TARGET qt_demo
#     POST_BUILD
#     COMMAND ${QT_DEPLOY_COMMAND}
# )
