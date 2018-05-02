###########################
# Main exe
###########################
file(GLOB main_SRC "*.cpp")

add_executable(graph ${main_SRC})
add_dependencies(graph catch)
target_include_directories(graph PUBLIC ${CATCH_DIR})
