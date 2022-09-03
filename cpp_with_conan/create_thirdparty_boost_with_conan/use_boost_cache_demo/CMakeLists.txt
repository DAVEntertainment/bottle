cmake_minimum_required(VERSION 3.15)
project(demo CXX)

set(Boost_DEBUG 1)
find_package(Boost 1.79.0 REQUIRED)
# find_package(Boost 1.79.0 REQUIRED Components chrono)
# find_package(Boost CONFIG REQUIRED Components filestystem)

add_executable(demo
    demo.cpp
)
target_link_libraries(demo
    PRIVATE
        # Boost::filesystem
        Boost::chrono
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
