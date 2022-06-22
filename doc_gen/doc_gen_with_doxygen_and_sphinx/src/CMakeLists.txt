cmake_minimum_required(VERSION 3.15)
project(demo)

add_executable(demo
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/common/math.cpp
    ${CMAKE_CURRENT_LIST_DIR}/common/math.h
    ${CMAKE_CURRENT_LIST_DIR}/biz/show_biz.cpp
    ${CMAKE_CURRENT_LIST_DIR}/biz/show_biz.h
)

target_include_directories(demo
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/
)

# Log configurations
message(STATUS "Configurations for src:")
message(STATUS "    CMAKE_CURRENT_LIST_DIR      = ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "    CMAKE_CURRENT_BINARY_DIR    = ${CMAKE_CURRENT_BINARY_DIR}")
