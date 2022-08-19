cmake_minimum_required(VERSION 3.16.6)
project(lib_ref_demo)

# add path for find_package
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/library/.install)

# find static library we made
find_package(Demo CONFIG)

# # @@@ Debug info: static library Demo::demo location
# if(Demo_FOUND)
#     message(STATUS "@@@@ Demo_FOUND @@@@@@@@@@@ ")    
#     get_target_property(_import_location Demo::demo IMPORTED_LOCATION_RELEASE)
#     message(STATUS "@@@ import location(release): ${_import_location}")
#     get_target_property(_import_location Demo::demo IMPORTED_LOCATION_DEBUG)
#     message(STATUS "@@@ import location(debug): ${_import_location}")
# ELSE()
#     message(STATUS "@@@@ Demo_NOT-FOUND @@@@@@@ ")
# ENDIF()

# add ref demo exe
add_executable(lib_ref_demo
    ref.cpp
)

# link static library to ref demo
target_link_libraries(lib_ref_demo PUBLIC Demo::demo)

# # @@@ Debug info: inherit include directory from static library demo
# get_target_property(_inc lib_ref_demo INCLUDE_DIRECTORIES)
# message(STATUS "@@@@ including: ${_inc} @@@@@@@ ")
