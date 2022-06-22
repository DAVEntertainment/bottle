cmake_minimum_required(VERSION 3.5.1)
project(demo CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(demo
    Main.cpp
    Demo.h
    Common.h
    Share0.cpp
    Share1.cpp
)

install(
    TARGETS demo
    RUNTIME DESTINATION ${CMAKE_CURRENT_LIST_DIR}
)
