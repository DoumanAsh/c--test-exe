###########################
# Main exe
###########################
file(GLOB main_SRC "*.cpp")

add_executable(add_two_numbers ${main_SRC})
add_dependencies(add_two_numbers catch)
target_include_directories(add_two_numbers PUBLIC ${CATCH_DIR})
