cmake_minimum_required(VERSION 3.5.1)
project(demo CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(test_thread0
    TestThread0.cpp
)

add_executable(test_thread1
    TestThread1.cpp
)

install(
    TARGETS
        test_thread0
        test_thread1
    RUNTIME DESTINATION ${CMAKE_CURRENT_LIST_DIR}
)
