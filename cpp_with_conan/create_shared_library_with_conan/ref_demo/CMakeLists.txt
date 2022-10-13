cmake_minimum_required(VERSION 3.16.6)
project(lib_ref_demo)

# find shared library we made
find_package(add REQUIRED CONFIG COMPONENTS add)

# add ref demo exe
add_executable(lib_ref_demo
    ref.cpp
)

# link shared library to ref
target_link_libraries(lib_ref_demo
    PRIVATE
        Add::add
)

# config install paths
install(
    TARGETS lib_ref_demo
    RUNTIME DESTINATION bin
)

#######################################################
# debug lines
#######################################################
get_property(_targets DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY IMPORTED_TARGETS)
message(STATUS "@@@ IMPORTED_TARGETS:")
foreach(_t ${_targets})
    message(STATUS "  ${_t}")
endforeach()

get_target_property(_value Add::add INTERFACE_LINK_OPTIONS)
message(STATUS "@@@ Add::add INTERFACE_LINK_OPTIONS = ${_value}")

get_target_property(_value Add::add INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "@@@ Add::add INTERFACE_INCLUDE_DIRECTORIES = ${_value}")

get_target_property(_value Add::add INTERFACE_COMPILE_DEFINITIONS)
message(STATUS "@@@ Add::add INTERFACE_COMPILE_DEFINITIONS = ${_value}")

get_target_property(_value Add::add INTERFACE_COMPILE_OPTIONS)
message(STATUS "@@@ Add::add INTERFACE_COMPILE_OPTIONS = ${_value}")

get_target_property(_value Add::add INTERFACE_LINK_LIBRARIES)
message(STATUS "@@@ Add::add INTERFACE_LINK_LIBRARIES = ${_value}")
