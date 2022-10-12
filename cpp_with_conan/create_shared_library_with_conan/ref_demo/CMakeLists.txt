cmake_minimum_required(VERSION 3.16.6)
project(lib_ref_demo)

# find shared library we made
find_package(add REQUIRED)
# find_package(add REQUIRED CONFIG COMPONENTS add)
get_property(_targets DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY IMPORTED_TARGETS)
message(STATUS "@@@ IMPORTED_TARGETS:")
foreach(_t ${_targets})
    message(STATUS "  ${_t}")
endforeach()

# add ref demo exe
add_executable(lib_ref_demo
    ref.cpp
)

# link shared library to ref
target_link_libraries(lib_ref_demo
    PRIVATE
        Add::add
)

# # install library to output dir after build done, so that lib_ref_demo.exe can find demo.dll
# add_custom_command(
#     TARGET lib_ref_demo
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Add::add> $<TARGET_FILE_DIR:lib_ref_demo>
#     COMMAND ${CMAKE_COMMAND} -E echo "Install Add::add runtime for lib_ref_demo"
# )
