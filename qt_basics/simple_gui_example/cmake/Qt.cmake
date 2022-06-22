cmake_minimum_required(VERSION 3.5.1)
include_guard(DIRECTORY)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Change the path below to match the location of your QT installation on your machine.
# Or comment out the following line, add the QT cmake scripts path to the system environment variable `Path'.
list(APPEND CMAKE_PREFIX_PATH "D:/4_software/Qt/5.12.12/msvc2017_64/lib/cmake")

set(_REQUIRED_QT_COMPONENTS Gui Core Widgets)
set(REQUIRED_QT_COMPONENTS)
foreach(_component ${_REQUIRED_QT_COMPONENTS})
    list(APPEND REQUIRED_QT_COMPONENTS "Qt5::${_component}")
endforeach()

find_package(Qt5
    COMPONENTS
        ${_REQUIRED_QT_COMPONENTS}
    REQUIRED
)

unset(_component)
unset(_REQUIRED_QT_COMPONENTS)