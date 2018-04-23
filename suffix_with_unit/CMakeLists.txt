###########################
# Main exe
###########################
file(GLOB main_SRC "*.cpp")

add_executable(suffix_with_unit ${main_SRC})
add_dependencies(suffix_with_unit catch)
target_include_directories(suffix_with_unit PUBLIC ${CATCH_DIR})
