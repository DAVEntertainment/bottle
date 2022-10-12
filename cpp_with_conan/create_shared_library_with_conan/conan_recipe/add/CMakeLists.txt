cmake_minimum_required(VERSION 3.16.6)
project(Demo)

##################################################################
# project configurations
##################################################################
set(CMAKE_DEBUG_POSTFIX d)

##################################################################
# target configurations
##################################################################
set(TARGET_NAME add)
set(TARGET_NAMESPACE Add)

set(TARGET_RUNTIME_INSTALL_DIR bin)
set(TARGET_ARCHIVE_INSTALL_DIR lib)
set(TARGET_LIBRARY_INSTALL_DIR lib)
set(TARGET_PUBLIC_HEADER_INSTALL_DIR include)
set(TARGET_PRIVATE_HEADER_INSTALL_DIR include/private)

##################################################################
# target sources
##################################################################
set(TARGET_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)
set(TARGET_SOURCES
    add.cpp
)
set(TARGET_PUBLIC_HEADERS
    add.h
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
