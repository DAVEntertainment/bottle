cmake_minimum_required(VERSION 3.16.6)
project(lib_ref_demo)

# add path for find_package
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/library/.install)

# find shared library we made
find_package(Demo CONFIG)

# add ref demo exe
add_executable(lib_ref_demo
    ref.cpp
)

# link shared library to ref demo
target_link_libraries(lib_ref_demo PUBLIC Demo::demo)

# install Demo::demo library to output dir after build done, so that lib_ref_demo.exe can find demo.dll
add_custom_command(
    TARGET lib_ref_demo
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Demo::demo> $<TARGET_FILE_DIR:lib_ref_demo>
    COMMAND ${CMAKE_COMMAND} -E echo "Install Demo::demo runtime for lib_ref_demo"
)
