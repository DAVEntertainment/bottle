
function(show_all_found_targets)
    get_property(_targets DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY IMPORTED_TARGETS)
    message(STATUS "IMPORTED_TARGETS:")
    foreach(_t ${_targets})
        message(STATUS "  ${_t}")
    endforeach()
endfunction(show_all_found_targets)
