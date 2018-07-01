###########################
# Main exe
###########################
file(GLOB main_SRC "*.cpp")

add_executable(find_distinct_pairs ${main_SRC})
add_dependencies(find_distinct_pairs catch)
target_include_directories(find_distinct_pairs PUBLIC ${CATCH_DIR})
