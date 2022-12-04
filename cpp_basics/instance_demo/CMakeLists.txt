cmake_minimum_required(VERSION 3.5.1)
project(demo CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(demo
    ref.h
    test.cpp
)

install(
    TARGETS demo
)

enable_testing()
add_test(NAME demo COMMAND demo)
