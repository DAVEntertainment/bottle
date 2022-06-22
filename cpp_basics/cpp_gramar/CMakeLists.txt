cmake_minimum_required(VERSION 3.5.1)
project(demo CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest CONFIG REQUIRED)

add_executable(demo
    ${CMAKE_CURRENT_LIST_DIR}/ReferenceTester.h
    ${CMAKE_CURRENT_LIST_DIR}/ReferenceTester.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TestBind.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TestLock.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TestReference.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TestTemplate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TestVector.cpp
)
target_link_libraries(demo
    PUBLIC
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

enable_testing()
add_test(NAME demo COMMAND demo)
