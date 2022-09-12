cmake_minimum_required(VERSION 3.16.6)
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

set(TARGET_RUNTIME_INSTALL_DIR bin)
set(TARGET_ARCHIVE_INSTALL_DIR lib)
set(TARGET_LIBRARY_INSTALL_DIR lib)
set(TARGET_PUBLIC_HEADER_INSTALL_DIR include)
set(TARGET_PRIVATE_HEADER_INSTALL_DIR include/private)

##################################################################
# target sources
##################################################################
set(TARGET_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/public
    ${CMAKE_CURRENT_SOURCE_DIR}/private
)
set(TARGET_SOURCES
    imp.cpp
)
set(TARGET_PUBLIC_HEADERS
    public/demo/add.h
    public/demo/declare.h
)
set(TARGET_PRIVATE_HEADERS
    private/priv_demo/del.h
)

##################################################################
# library properties
##################################################################
add_library(${TARGET_NAME} SHARED ${TARGET_PUBLIC_HEADERS} ${TARGET_PRIVATE_HEADERS} ${TARGET_SOURCES})
# set_target_properties(${TARGET_NAME} PROPERTIES
#     MSVC_RUNTIME_LIBRARY MultiThreadedDLL
# )

# set public headers, 
#   cmake will install them automatically to
#   PUBLIC_HEADER DESTINATION
set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${TARGET_PUBLIC_HEADERS}"
    # PRIVATE_HEADER "${TARGET_PRIVATE_HEADERS}" # if PRIVATE_HEADER is given, then will be installed, too
)
# add include directories for generating shared library, as property INCLUDE_DIRECTORIES
target_include_directories(${TARGET_NAME} PRIVATE
    ${TARGET_INCLUDE_DIRS}
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
target_compile_definitions(${TARGET_NAME} PRIVATE -DDEMO_EXPORT_API)

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
