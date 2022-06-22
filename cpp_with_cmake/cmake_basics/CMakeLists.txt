cmake_minimum_required(VERSION 3.15)
project(demo)

option(DEBUG_RUN_LOCAL_CMAKE_TEST   "Run local cmake tests"                            ON)
option(DEBUG_SHOW_INCLUDE_ENTRY     "Show include files for DEBUG purpose"             ON)
OPTION(VERBOSE                      "Show verbose information for DEBUG purpose"       ON)

include(demo.cmake)

show_c_flags()
show_cxx_flags()
show_linker_flags()
