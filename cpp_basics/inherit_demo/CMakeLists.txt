cmake_minimum_required(VERSION 3.5.1)
project(demo CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(demo
    Main.cpp
    Demo0.h
    Demo1.h
)

install(
    TARGETS demo
    RUNTIME DESTINATION ${CMAKE_CURRENT_LIST_DIR}
)
