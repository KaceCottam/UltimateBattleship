# Registers a spike.
# Usage: register_spike(NAME <name>
#                       SOURCES <all source files>
#                       DEPENDENCIES <sfml dependencies>)
# Output executable is in ${CW_BIN} or bin/
function(register_spike)
  set(SingleArgs NAME)
  set(MultiArgs SOURCES DEPENDENCIES)
  cmake_parse_arguments(SPIKE NONE "${SingleArgs}" "${MultiArgs}" ${ARGV})

  project(${SPIKE_NAME})
  add_executable(${SPIKE_NAME} ${SPIKE_SOURCES})
  target_link_libraries(${SPIKE_NAME} ${SPIKE_DEPENDENCIES})
  target_link_directories(${SPIKE_NAME} PRIVATE ${SFML_INCLUDE})
  set_target_properties(${SPIKE_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${CW_BIN})
endfunction()

register_spike(NAME WindowAndDrawBall
               SOURCES WindowAndDrawBall.cpp
               DEPENDENCIES sfml-graphics fmt::fmt spdlog::spdlog)