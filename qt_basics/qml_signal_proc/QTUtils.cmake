
function(deploy_qt_shared_library aSharedLibrary)
    
endfunction(deploy_qt_shared_library)

# deploy_qt_executable(aExecutable)
# deploy_qt_executable(aExecutable aQMLRoot)
function(deploy_qt_executable aExecutable)


endfunction(deploy_qt_executable)

function(print_list aListName aList)
    message(STATUS "${aListName}:")
    foreach(_e ${aList})
        message(STATUS "    ${_e}")
    endforeach()
endfunction(print_list)

function(get_dirs_from_paths aOutDirs aPaths)
    set(_dirs)
    foreach(_f ${_QMLFiles})
        get_filename_component(_d ${_f} DIRECTORY)
        list(APPEND _dirs ${_d})
    endforeach()
    list(REMOVE_DUPLICATES _dirs)
    set(${aOutDirs} ${_dirs} PARENT_SCOPE)
endfunction(get_dirs_from_paths)
