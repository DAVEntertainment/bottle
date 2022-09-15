cmake_minimum_required(VERSION 3.16.6)
project(shared_a)

##################################################################
# project configurations
##################################################################
set(CMAKE_DEBUG_POSTFIX d)

##################################################################
# target configurations
##################################################################
set(TARGET_NAME shared_a)
set(TARGET_NAMESPACE Lib)

set(TARGET_RUNTIME_INSTALL_DIR bin)
set(TARGET_ARCHIVE_INSTALL_DIR lib)
set(TARGET_LIBRARY_INSTALL_DIR lib)
set(TARGET_PUBLIC_HEADER_INSTALL_DIR include)
set(TARGET_PRIVATE_HEADER_INSTALL_DIR include/private)

##################################################################
# dependencies
##################################################################
include(${CMAKE_CURRENT_LIST_DIR}/../utils.cmake)

# add path for find_package
list(APPEND CMAKE_PREFIX_PATH
    ${CMAKE_CURRENT_LIST_DIR}/../static/.install_v0
)

# find shared library we made
find_package(static REQUIRED CONFIG)
show_all_found_targets()

##################################################################
# target sources
##################################################################
set(TARGET_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)
set(TARGET_SOURCES
    imp.cpp
)
set(TARGET_PUBLIC_HEADERS
    show_a.h
)

##################################################################
# library properties
##################################################################
add_library(${TARGET_NAME} SHARED ${TARGET_PUBLIC_HEADERS} ${TARGET_SOURCES})
set_target_properties(${TARGET_NAME} PROPERTIES
    MSVC_RUNTIME_LIBRARY MultiThreadedDLL
)

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${TARGET_PUBLIC_HEADERS}"
)
target_include_directories(${TARGET_NAME} PRIVATE
    ${TARGET_INCLUDE_DIRS}
)
target_link_libraries(${TARGET_NAME} PRIVATE
    Lib::static
)

# speicify interface include directories,
#   as property INTERFACE_INCLUDE_DIRECTORIES and INTERFACE_SYSTEM_INCLUDE_DIRECTORIES,
#   the interface include directories will be passed to the target which refers demo
string(REPLACE ";" "$<SEMICOLON>" _include_dirs "${TARGET_INCLUDE_DIRS}")
target_include_directories(${TARGET_NAME} SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${_include_dirs}>"
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${TARGET_PUBLIC_HEADER_INSTALL_DIR}>"
)

# add macro DEMO_EXPORT_API so that *.h will enable dllexport
target_compile_definitions(${TARGET_NAME} PRIVATE -DDEMOA_EXPORT_API)

##################################################################
# install target
##################################################################
# config install paths
install(
    TARGETS ${TARGET_NAME}
    EXPORT ${TARGET_NAME}
    RUNTIME DESTINATION ${TARGET_RUNTIME_INSTALL_DIR}
    ARCHIVE DESTINATION ${TARGET_ARCHIVE_INSTALL_DIR}
    LIBRARY DESTINATION ${TARGET_LIBRARY_INSTALL_DIR}
    PUBLIC_HEADER DESTINATION ${TARGET_PUBLIC_HEADER_INSTALL_DIR}
    PRIVATE_HEADER DESTINATION ${TARGET_PRIVATE_HEADER_INSTALL_DIR}
)

# install <TARGET>Targets*.cmake files
install(
    EXPORT ${TARGET_NAME}
    FILE ${TARGET_NAME}Targets.cmake
    NAMESPACE ${TARGET_NAMESPACE}:: # Defines namespace in XXXTargets.cmake
    DESTINATION lib/cmake/${TARGET_NAME}
)

##################################################################
# <TARGET>Config.cmake and <TARGET>ConfigVersion.cmake 
##################################################################
# CMakePackageConfigHelpers provides
#   write_basic_package_version_file
#   configure_package_config_file
include(CMakePackageConfigHelpers)
# generate <TARGET>ConfigVersion.cmake file
write_basic_package_version_file(
    ${TARGET_NAME}ConfigVersion.cmake
    VERSION 1.0.0
    COMPATIBILITY SameMajorVersion # AnyNewerVersion|SameMajorVersion|SameMinorVersion|ExactVersion
)
# generate <TARGET>Config.cmake file
configure_package_config_file(
    PackageConfig.cmake.in ${TARGET_NAME}Config.cmake
    INSTALL_DESTINATION  lib/cmake/${TARGET_NAME}
)
# install <TARGET>Config.cmake and <TARGET>ConfigVersion.cmake file
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}ConfigVersion.cmake
    DESTINATION lib/cmake/${TARGET_NAME}
)
