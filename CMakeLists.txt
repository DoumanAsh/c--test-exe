###########################
# Init
##########################
cmake_minimum_required(VERSION 3.5)
set(MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.cmake/Modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${MODULE_DIR})
include(LazyUtils)

set(CMAKE_CXX_STANDARD 17)
# Generates compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(VnTextTrim LANGUAGES CXX VERSION)

###########################
# Compiler flags
##########################
if (WIN32)
    # For MinGW we assume that minimum runtime is Vista
    set_gcc_flags_if("-D_WIN32_WINNT=0x0600")

    # Enforces WinAPI to use unicode version of functions
    add_definitions(-DUNICODE)
    add_definitions(-D_UNICODE)
    enable_static_crt()
    remove_msvc_default_warning_level()
endif()
###########################
# Output dir
##########################
set_output_dir("${CMAKE_BINARY_DIR}/dist")

###########################
# Max compile warnings for own code only
##########################
set_msvc_flags_if("/W4 /source-charset:utf-8")
set_gcc_flags_if("-Wall -Wextra")

###########################
# 3PP
##########################
#add_subdirectory("3pp/")

###########################
# LIB
##########################
#add_subdirectory("lib/")

###########################
# SRC
##########################
add_subdirectory("get_twice_num/")
add_subdirectory("multi_queue_processing/")
