###########################
# Main exe
###########################
file(GLOB main_SRC "*.cpp")

add_executable(find_two_sum ${main_SRC})
add_dependencies(find_two_sum catch)
target_include_directories(find_two_sum PUBLIC ${CATCH_DIR})
