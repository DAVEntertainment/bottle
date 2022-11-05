cmake_minimum_required(VERSION 3.16.6)
project(lib_ref_demo)

# add path for find_package
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/library/.install)

# find shared library we made
find_package(Demo CONFIG)


#################################################################################
# debug lines, lines BELOW this can be deleted                                  #
#################################################################################
# packages found                                                                #
get_property(_packages_found GLOBAL PROPERTY PACKAGES_FOUND)                    #
message(STATUS "@@@ PACKAGES_FOUND: ${_packages_found}")                        #
                                                                                #
# imported targtets (from cmake 3.21)                                           #
get_property(_targets DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY IMPORTED_TARGETS)  #
message(STATUS "@@@ IMPORTED_TARGETS: ${_targets}")                             #
#################################################################################
# debug lines, lines ABOVE this can be deleted                                  #
#################################################################################


# add ref demo exe
add_executable(lib_ref_demo
    ref.cpp
)

# link shared library to ref demo
target_link_libraries(lib_ref_demo PUBLIC Demo::demo)

# install ref demo
install(TARGETS lib_ref_demo)

# install runtime(.dll files form dependent libraries) for ref demo
install(IMPORTED_RUNTIME_ARTIFACTS Demo::demo) # new in CMake 3.21
