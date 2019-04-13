project(WindowAndDrawBall)
add_executable(WindowAndDrawBall WindowAndDrawBall.cpp)
target_link_libraries(WindowAndDrawBall sfml-graphics)
target_include_directories(WindowAndDrawBall PRIVATE ${SFML_INCLUDE})
set_target_properties(WindowAndDrawBall
                      PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CW_BIN})