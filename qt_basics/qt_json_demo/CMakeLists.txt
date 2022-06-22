cmake_minimum_required(VERSION 3.5.1)
project(qt_json_demo CXX)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/function.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/qt.cmake)

set(TARGET_NAME qt_json_demo)

add_executable(${TARGET_NAME}
    qt_json.cpp
    qt_json.h
    main.cpp
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
        ${REQUIRED_QT_COMPONENTS}
)

set_target_properties(${TARGET_NAME}
    PROPERTIES
        WIN32_EXECUTABLE 1
        TARGET_FILE_DIR  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

copy_file_to_destination(
    FOR_TARGET ${TARGET_NAME}
    DESTINATION $<TARGET_FILE_DIR:${TARGET_NAME}>
    TARGETS
        ${REQUIRED_QT_COMPONENTS}
)
