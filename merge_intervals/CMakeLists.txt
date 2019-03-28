###########################
# Main exe
###########################
file(GLOB main_SRC "*.cpp")

add_executable(merge_intervals ${main_SRC})
set_target_properties(merge_intervals PROPERTIES CXX_STANDARD 11)
