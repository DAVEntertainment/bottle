cmake_minimum_required(VERSION 3.5.1)
include_guard(DIRECTORY)

# cmake configurations
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CONFIGURATION_TYPES Debug Release
    CACHE STRING "Build configuration types" FORCE)

set(CMAKE_CXX_STANDARD 17
    CACHE INTERNAL "C++ standard" FORCE)

set(CMAKE_DEBUG_POSTFIX d)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/.$<LOWER_CASE:$<CONFIG>>)
