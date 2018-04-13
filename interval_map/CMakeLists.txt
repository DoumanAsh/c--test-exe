###########################
# Main exe
###########################
file(GLOB main_SRC "*.cpp")

add_executable(interval_map ${main_SRC})
add_dependencies(interval_map catch)
target_include_directories(interval_map PUBLIC ${CATCH_DIR})
