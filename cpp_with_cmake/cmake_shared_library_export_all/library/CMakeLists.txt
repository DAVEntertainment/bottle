cmake_minimum_required(VERSION 3.23)
project(demo)

##################################################################
# project configurations
##################################################################
set(CMAKE_DEBUG_POSTFIX d)

##################################################################
# target configurations
##################################################################
set(TARGET_NAME demo)
set(TARGET_NAMESPACE Demo)

##################################################################
# target sources
##################################################################
set(TARGET_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
set(TARGET_SOURCES
    src/add.cpp
    src/del.cpp
    src/product.cpp
)
set(TARGET_PUBLIC_HEADERS
    include/demo/add.h
    include/demo/declare.h
)
set(TARGET_PRIVATE_HEADERS
    src/del.h
)

##################################################################
# library properties
##################################################################
add_library(${TARGET_NAME} SHARED ${TARGET_SOURCES})
# set_target_properties(${TARGET_NAME} PROPERTIES
#     MSVC_RUNTIME_LIBRARY MultiThreadedDLL
# )

# set public headers as target's file set (new in CMake 3.23)
target_sources(${TARGET_NAME}
    PUBLIC
        FILE_SET    exported_headers
        TYPE        HEADERS         # specify type as HEADERS, so that cmake will install them automatically to PUBLIC_HEADER DESTINATION
        BASE_DIRS   ${TARGET_INCLUDE_DIRS}
        FILES       ${TARGET_PUBLIC_HEADERS}
)

# speicify interface include directories,
#   as property INTERFACE_INCLUDE_DIRECTORIES and INTERFACE_SYSTEM_INCLUDE_DIRECTORIES,
#   the interface include directories will be passed to the target which refers demo
string(REPLACE ";" "$<SEMICOLON>" _include_dirs "${TARGET_INCLUDE_DIRS}")
target_include_directories(${TARGET_NAME} SYSTEM
    INTERFACE
        "$<BUILD_INTERFACE:${_include_dirs}>"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
    PRIVATE # add include directories for generating shared library, as property INCLUDE_DIRECTORIES
        ${TARGET_INCLUDE_DIRS}
)

# add macro DEMO_EXPORT_API so that *.h will enable dllexport
target_compile_definitions(${TARGET_NAME} PRIVATE -DDEMO_EXPORT_API)

##################################################################
# install target
##################################################################
# config install paths
install(
    TARGETS ${TARGET_NAME}
    EXPORT ${TARGET_NAME}
    FILE_SET exported_headers
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
