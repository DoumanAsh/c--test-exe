###########################
# Main exe
###########################
file(GLOB main_SRC "*.cpp")

add_executable(what_a_nice_day ${main_SRC})
set_target_properties(what_a_nice_day PROPERTIES CXX_STANDARD 11)
