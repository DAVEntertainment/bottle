cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
include_guard() # make sure this can be included for once only

#=========================================================================================
# options
#=========================================================================================
option(DEBUG_RUN_LOCAL_CMAKE_TEST   "Run local cmake tests"                            OFF)
option(DEBUG_SHOW_INCLUDE_ENTRY     "Show include files for DEBUG purpose"             OFF)
OPTION(VERBOSE                      "Show verbose information for DEBUG purpose"       OFF)


#=========================================================================================
# utility
#=========================================================================================
function(show_include path)
    if(DEBUG_SHOW_INCLUDE_ENTRY)
        message(STATUS "Include : ${path}")
    endif()
endfunction()
show_include(${CMAKE_CURRENT_LIST_FILE})


function(verbose_message info)
    if(VERBOSE)
        message(STATUS "[VERBOSE] ${info}")
    endif()
endfunction()


function(show_c_flags)
    message(STATUS "CMAKE_C_FLAGS                = ${CMAKE_C_FLAGS}")
    message(STATUS "CMAKE_C_FLAGS_MINSIZEREL     = ${CMAKE_C_FLAGS_MINSIZEREL}")
    message(STATUS "CMAKE_C_FLAGS_RELEASE        = ${CMAKE_C_FLAGS_RELEASE}")
    message(STATUS "CMAKE_C_FLAGS_RELWITHDEBINFO = ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
    message(STATUS "CMAKE_C_FLAGS_DEBUG          = ${CMAKE_C_FLAGS_DEBUG}")
endfunction()


function(show_cxx_flags)
    message(STATUS "CMAKE_CXX_FLAGS                = ${CMAKE_CXX_FLAGS}")
    message(STATUS "CMAKE_CXX_FLAGS_MINSIZEREL     = ${CMAKE_CXX_FLAGS_MINSIZEREL}")
    message(STATUS "CMAKE_CXX_FLAGS_RELEASE        = ${CMAKE_CXX_FLAGS_RELEASE}")
    message(STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO = ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    message(STATUS "CMAKE_CXX_FLAGS_DEBUG          = ${CMAKE_CXX_FLAGS_DEBUG}")
endfunction()


function(show_linker_flags)
    message(STATUS "CMAKE_EXE_LINKER_FLAGS                = ${CMAKE_EXE_LINKER_FLAGS}")
    message(STATUS "CMAKE_EXE_LINKER_FLAGS_MINSIZEREL     = ${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL}")
    message(STATUS "CMAKE_EXE_LINKER_FLAGS_RELEASE        = ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
    message(STATUS "CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO = ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}")
    message(STATUS "CMAKE_EXE_LINKER_FLAGS_DEBUG          = ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
endfunction()


function(show_list list_in keyword)
    if(NOT "" STREQUAL "${keyword}")
        message(STATUS "${keyword} :")
    else()
        message(STATUS "show list :")
    endif()
    foreach(ELEMENT ${list_in})
        message(STATUS "    ${ELEMENT}")
    endforeach()
endfunction()


# test if given variables are emtpy (not set)
function(validate_variables)
    SET(VALIDATION_FAILED false)
    foreach(A ${ARGV}) # this works for "A;B;C;D", which suit arguments format
        if("" STREQUAL "${${A}}")
            message(WARNING "validate_variables : ${A} not set")
            SET(VALIDATION_FAILED true)
        endif()
    endforeach()
    if(VALIDATION_FAILED)
        message(FATAL_ERROR "validate_variables : failed to validate variables ${ARGV}, see detailed information from above warnings")
    endif()
endfunction()


# validate variable in given strings(as list), case ignored
function(validate_string_case_ignored var values keyword)
    string(TOUPPER "${var}" var)
    string(TOUPPER "${values}" values)
    validate_string(${var} ${values} ${keyword})
endfunction()


function(validate_string var values keyword)
    if(NOT "${var}" IN_LIST values)
        message(FATAL_ERROR "validate_string: ${keyword} validation failed, got ${var}, available : ${values}")
    endif()
endfunction()


# validate configurations
# i.e.
#   SET(CFL_TYPES FILE MEMONLY MIX)
#   SET(CFL_TYPE  a_joke) # "a_joke" is a bad example. "File" is a good example. First value as default.
#   validate_configration(CFL_TYPE CFL_TYPES CFL_TYPE)
function(validate_configuration
    config_var_name
    config_values_var_name
    description
)
    # message(STATUS "enter validate_configuration : ${config_var_name} ${config_values_var_name} \"${description}\"")
    if("" STREQUAL "${${config_values_var_name}}")
        message(FATAL_ERROR "validate_configration: ${config_var_name} available choices not set")
    endif()
    string(TOUPPER "${${config_values_var_name}}" values)
    # message(STATUS "values : ${values}")
    if("" STREQUAL "${${config_var_name}}")
        list(GET values 0 DEFAULT_CONFIG_VALUE)
        set(config ${DEFAULT_CONFIG_VALUE})
    else()
        string(TOUPPER "${${config_var_name}}" config)
    endif()
    # message(STATUS "config : ${config}")
    if(NOT "${config}" IN_LIST values)
        message(FATAL_ERROR "validate_configration: ${config_var_name} validation failed, got ${config}, available : ${values}")
    endif()
    set(${config_var_name} ${config} CACHE STRING "$description" FORCE)
    set_property(CACHE ${config_var_name} PROPERTY STRINGS ${values})
    set(${config_values_var_name} ${values} CACHE INTERNAL "$description" FORCE)
endfunction()


function(validate_cmake_build_type)  # CMAKE_CONFIGURATION_TYPES && CMAKE_BUILD_TYPE should be set
    if(WIN32)
        if("" STREQUAL "${CMAKE_CONFIGURATION_TYPES}")
            message(FATAL_ERROR "validate_configration: ${config_var_name} available choices not set")
        endif()
        set(CMAKE_CONFIGURATION_TYPES ${CMAKE_CONFIGURATION_TYPES} CACHE STRING "Avalable build types" FORCE)
    else()
        if("" STREQUAL "${CMAKE_CONFIGURATION_TYPES}") # default configurations for linux is R&D
            set(CMAKE_CONFIGURATION_TYPES "Release;Debug")
        endif()
        validate_configuration(CMAKE_BUILD_TYPE CMAKE_CONFIGURATION_TYPES "Build type (${CMAKE_CONFIGURATION_TYPES})")
    endif()
    message(STATUS "Detecting build type: ${CMAKE_BUILD_TYPE}")
endfunction()


function(get_sub_dirs sub_dirs root)
    FILE(GLOB children RELATIVE ${root} ${root}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${root}/${child})
            list(APPEND found_sub_dirs ${child})
        endif()
    endforeach()
    SET(${sub_dirs} ${found_sub_dirs} PARENT_SCOPE)
endfunction()

#=========================================================================================
# local test
#=========================================================================================
if(DEBUG_RUN_LOCAL_CMAKE_TEST)
    # test : macro vs. function
    macro(test_macro_argument_change arg)
        message("=== Call macro ===")
        message("arg = ${arg}")
        set(arg "abc")
        message("# After change the value of arg.")
        message("arg = ${arg}")
    endmacro()
    
    function(test_function_argument_change arg)
        message("=== Call function ===")
        message("arg = ${arg}")
        set(arg "abc")
        message("# After change the value of arg.")
        message("arg = ${arg}")
    endfunction()
    
    set(test_macro_argument_change_var "ABC")
    test_macro_argument_change(${test_macro_argument_change_var})
    test_function_argument_change(${test_macro_argument_change_var})
    message("=== Global var ===")
    message("arg = ${arg}")
    # function vs. macro
    # function
    #   function WILL overwrite function scope ARGUMENT variables back
    #   so you CAN change ARGUMENT varaibles in functions
    # macro
    #   macro WILL NOT overwrite macro scope ARGUMENT varaibles back
    #   so you CAN NOT change ARGUMENT varaibles in macros
    # we can understand this as macro add a const decoration to function (i.e. c++ : void AClass::AMethod(void) CONST)
    # BOTH funcion && macro can change global varaibles
    # what the document say (Macro vs Function):
    #   The macro command is very similar to the function() command. Nonetheless, there are a few important differences.
    #   In a function, ARGN, ARGC, ARGV and ARGV0, ARGV1, �� are true variables in the usual CMake sense.
    #   In a macro, they are not, they are string replacements much like the C preprocessor would do with a macro.
    #   Another difference between macros and functions is the control flow.
    #   A function is executed by transferring control from the calling statement to the function body.
    #   A macro is executed as if the macro body were pasted in place of the calling statement.
    #   This has the consequence that a return() in a macro body does not just terminate execution of the macro;
    #   rather, control is returned from the scope of the macro call.
    #   To avoid confusion, it is recommended to avoid return() in macros altogether.
endif()