cmake_minimum_required(VERSION 3.16.6)
project(lib_ref_demo)

include(${CMAKE_CURRENT_LIST_DIR}/utils.cmake)

# add path for find_package
list(APPEND CMAKE_PREFIX_PATH
    ${CMAKE_CURRENT_LIST_DIR}/shared_a/.install
    ${CMAKE_CURRENT_LIST_DIR}/shared_b/.install
)

# find shared library we made
find_package(shared_a REQUIRED CONFIG)
find_package(shared_b REQUIRED CONFIG)
show_all_found_targets()

# add ref demo exe
add_executable(lib_ref_demo
    ref.cpp
)

# link shared library to ref demo
target_link_libraries(lib_ref_demo
    PRIVATE
        Lib::shared_a
        Lib::shared_b
)

# install Demo::demo library to output dir after build done, so that lib_ref_demo.exe can find demo.dll
add_custom_command(
    TARGET lib_ref_demo
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Lib::shared_a> $<TARGET_FILE_DIR:lib_ref_demo>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Lib::shared_b> $<TARGET_FILE_DIR:lib_ref_demo>
)
