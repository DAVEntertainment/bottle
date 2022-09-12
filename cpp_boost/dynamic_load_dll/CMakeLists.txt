cmake_minimum_required(VERSION 3.16.6)
project(lib_ref_demo)

# include boost cmake utils
include(${CMAKE_CURRENT_LIST_DIR}/../build_boost/boost_utils.cmake)

# add path for find_package
list(APPEND CMAKE_PREFIX_PATH
    ${CMAKE_CURRENT_LIST_DIR}/library/.install
    ${CMAKE_CURRENT_LIST_DIR}/../boost_1_79_0
)

# find shared library we made
set(Boost_DEBUG 1)
find_package(Boost 1.79.0 CONFIG REQUIRED COMPONENTS headers filesystem)
find_package(Demo REQUIRED CONFIG COMPONENTS demo)
show_all_found_targets()

# add ref demo exe
add_executable(lib_ref_demo
    ref.cpp
)

# link shared library to ref demo
target_link_libraries(lib_ref_demo PRIVATE Demo::demo Boost::headers Boost::filesystem)

# install Demo::demo library to output dir after build done, so that lib_ref_demo.exe can find demo.dll
add_custom_command(
    TARGET lib_ref_demo
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Demo::demo> $<TARGET_FILE_DIR:lib_ref_demo>
    COMMAND ${CMAKE_COMMAND} -E echo "Install Demo::demo runtime for lib_ref_demo"
)
