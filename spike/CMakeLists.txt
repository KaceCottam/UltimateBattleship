# Registers a spike.
# Usage: register_spike(NAME <name>
#                       SOURCES <all source files>
#                       INCLUDE <any include directories>
#                       DEPENDENCIES <sfml dependencies>)
# Output executable is in ${CW_BIN} or bin/
function(register_spike)
  set(SingleArgs NAME)
  set(MultiArgs SOURCES DEPENDENCIES OPTIONAL INCLUDE)
  cmake_parse_arguments(SPIKE NONE "${SingleArgs}" "${MultiArgs}" ${ARGV})

  project(${SPIKE_NAME})
  add_executable(${SPIKE_NAME} ${SPIKE_SOURCES})
  target_link_libraries(${SPIKE_NAME} ${SPIKE_DEPENDENCIES})
  target_link_directories(${SPIKE_NAME} PRIVATE ${SFML_INCLUDE} ${SPIKE_INCLUDE})
  set_target_properties(${SPIKE_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${CW_BIN})
endfunction()

# TODO: Make a function for registering dependencies so we dont need such a long
#       Sources section.

register_spike(NAME WindowAndDrawBall
               SOURCES "WindowAndDrawBall.cpp"
               DEPENDENCIES sfml-graphics fmt::fmt spdlog::spdlog)

register_spike(NAME ButtonTest
               SOURCES "ButtonTest.cpp"
                       "GUI/Button.hpp" "GUI/Clickable.hpp" "GUI/Hoverable.hpp"
                       "SFMLUtil/FileNotFoundException.hpp"
               DEPENDENCIES sfml-graphics fmt::fmt spdlog::spdlog)

register_spike(NAME BoardTest
              SOURCES "Board.cpp" "Board.h"
                      "Tile.cpp" "Tile.h"
                      "TestBoardMain.cpp"
              DEPENDENCIES sfml-graphics)

register_spike(NAME SceneManagerTest
               SOURCES "SceneManagerTest.cpp"
                       "GUI/GameEngine.hpp" "GUI/Scene.hpp"
                       "SFMLUtil/BadIndexError.hpp"
               DEPENDENCIES sfml-graphics fmt::fmt spdlog::spdlog)

register_spike(NAME BasicBattleship
                SOURCES "BasicBattleship.cpp" "Board.h" "TileMovement.hpp"
                "ShipPlacement.hpp" "FiringMechanism.hpp"
                DEPENDENCIES sfml-graphics)