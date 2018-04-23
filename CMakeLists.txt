cmake_minimum_required(VERSION 3.5)
set(MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.cmake/Modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${MODULE_DIR})
include(msvc)
include(gcc)

set(CMAKE_CXX_STANDARD 17)
project(test-exercise LANGUAGES CXX VERSION)

macro(set_output_dir dir)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${dir}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${dir}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/bin)
endmacro(set_output_dir)

set_output_dir("${CMAKE_BINARY_DIR}/dist")

msvc_remove_warning_level()
msvc_set_flags_if("/utf-8 /W4 /std:c++17")
gcc_set_flags_if("-Wall -Wextra")

include(catch.cmake)
###########################
# SRC
##########################
add_subdirectory("get_twice_num/")
add_subdirectory("multi_queue_processing/")
add_subdirectory("assign_level/")
add_subdirectory("interval_map/")
add_subdirectory("suffix_with_unit/")

###########################
# Linter
##########################
option(CLANG_TIDY "Enable Clang tidy checks" ON)
if (CLANG_TIDY)
    include(ClangTidy)
    enable_clang_tidy_for(assign_level)
endif()
