cmake_minimum_required(VERSION 3.15)
project(demo CXX)

find_package(GTest CONFIG REQUIRED)

add_executable(demo
    demo.cpp
)
target_link_libraries(demo
    PRIVATE
        GTest::gtest
        GTest::gtest_main
)

install(
    TARGETS demo

    # if target is library, target should be exported
    # EXPORT demo 

    # path to install static library build in target
    ARCHIVE DESTINATION lib

    # path to install shared library build in target
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin

    # path to install include build in target
    PUBLIC_HEADER DESTINATION include
)
