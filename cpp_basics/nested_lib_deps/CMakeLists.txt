cmake_minimum_required(VERSION 3.16.6)
project(nested_lib_deps)

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
add_executable(nested_lib_deps
    ref.cpp
)

# link shared library to ref demo
target_link_libraries(nested_lib_deps
    PRIVATE
        Lib::shared_a
        Lib::shared_b
)

# install Demo::demo library to output dir after build done, so that nested_lib_deps.exe can find demo.dll
add_custom_command(
    TARGET nested_lib_deps
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Lib::shared_a> $<TARGET_FILE_DIR:nested_lib_deps>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Lib::shared_b> $<TARGET_FILE_DIR:nested_lib_deps>
)
