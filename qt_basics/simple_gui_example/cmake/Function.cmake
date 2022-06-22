cmake_minimum_required(VERSION 3.5.1)
include_guard(DIRECTORY)

function(copy_file_to_destination)
    set(prefix COPY)
    set(options "")
    set(oneValueKeywords FOR_TARGET DESTINATION)
    set(multiValueKeywords FOLDERS FILES TARGETS)
    cmake_parse_arguments("${prefix}" "${options}" "${oneValueKeywords}" "${multiValueKeywords}" ${ARGN})

    foreach(_folder ${COPY_FOLDERS})
        add_custom_command(
            TARGET ${COPY_FOR_TARGET}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "To copy runtime folder to '${COPY_DESTINATION}' for target '${COPY_FOR_TARGET}': '${_folder}'"
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${_folder} ${COPY_DESTINATION}
        )
    endforeach()

    foreach(_file ${COPY_FILES})
        add_custom_command(
            TARGET ${COPY_FOR_TARGET}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "To copy runtime folder to '${COPY_DESTINATION}' for target '${COPY_FOR_TARGET}': '${_file}'"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${_file} ${COPY_DESTINATION}
        )
    endforeach()

    foreach(_target ${COPY_TARGETS})
        add_custom_command(
            TARGET ${COPY_FOR_TARGET}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "To copy runtime folder to '${COPY_DESTINATION}' for target '${COPY_FOR_TARGET}': '$<TARGET_FILE:${_target}>'"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${_target}> ${COPY_DESTINATION}
        )
    endforeach()

    unset(_folder)
    unset(_file)
    unset(_target)
endfunction(copy_file_to_destination)