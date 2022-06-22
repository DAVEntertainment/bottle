cmake_minimum_required(VERSION 3.5.1)
project(demo CXX)

set(CMAKE_RC_FLAGS
    "/v"
    CACHE STRING
    "Windows RC Compiler flags"
    FORCE
)

add_executable(demo
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/versioninfo.rc
)

install(
    TARGETS demo
    RUNTIME DESTINATION ${CMAKE_CURRENT_LIST_DIR}
)
