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

  set(SPIKE_OPTION_NAME "BUILD_${SPIKE_NAME}")
  option(${SPIKE_OPTION_NAME} OFF)
  if(${SPIKE_OPTION_NAME})
  project(${SPIKE_NAME})
  add_executable(${SPIKE_NAME} ${SPIKE_SOURCES})
  target_link_libraries(${SPIKE_NAME} ${SPIKE_DEPENDENCIES})
  target_link_directories(${SPIKE_NAME} PRIVATE ${SFML_INCLUDE} ${SPIKE_INCLUDE})
  set_target_properties(${SPIKE_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${CW_BIN}
                        CXX_STANDARD 17)
  endif()
endfunction()

# Registers a helping library.
# USage: register_helper(NAME <name>
#                        SOURCES <all source files>
#                        [DEPENDENCIES <all dependencies>]
#                        [INCLUDE <all additional include directories>])
function(register_helper)
  set(SingleArgs NAME)
  set(MultiArgs SOURCES OPTIONAL DEPENDENCIES INCLUDE)
  cmake_parse_arguments(HELP NONE "${SingleArgs}" "${MultiArgs}" ${ARGV})

  project(${HELP_NAME} C CXX)
  add_library(${HELP_NAME} ${HELP_SOURCES} static.cpp)
  target_link_libraries(${HELP_NAME} ${HELP_DEPENDENCIES})
  target_link_directories(${HELP_NAME} PRIVATE ${SFML_INCLUDE} ${HELP_INCLUDE})
  set_target_properties(${HELP_NAME}
                        PROPERTIES
                        CXX_STANDARD 17)
endfunction()

register_helper(NAME Clickable
                SOURCES "GUI/Clickable.hpp"
                DEPENDENCIES sfml-graphics)

register_helper(NAME Hoverable
                SOURCES "GUI/Hoverable.hpp"
                DEPENDENCIES sfml-graphics)

register_helper(NAME Button
                SOURCES "GUI/Button.hpp"
                DEPENDENCIES sfml-graphics Clickable Hoverable)

register_helper(NAME FileNotFoundException
                SOURCES "SFMLUtil/FileNotFoundException.hpp"
                DEPENDENCIES fmt::fmt spdlog::spdlog)

register_helper(NAME BadIndexError
                SOURCES "SFMLUtil/BadIndexError.hpp"
                DEPENDENCIES fmt::fmt spdlog::spdlog)

register_helper(NAME Scene
                SOURCES "GUI/Scene.hpp"
                DEPENDENCIES sfml-graphics)

register_helper(NAME GameEngine
                SOURCES "GUI/GameEngine.hpp"
                DEPENDENCIES sfml-graphics Scene BadIndexError
                             fmt::fmt spdlog::spdlog)

register_helper(NAME Ship
                SOURCES "Ship.hpp"
                DEPENDENCIES sfml-graphics)

register_helper(NAME Tile
                SOURCES "Tile.h" "Tile.cpp"
                DEPENDENCIES sfml-graphics)

register_helper(NAME Board
                SOURCES "Board.h" "Board.cpp"
                DEPENDENCIES sfml-graphics Ship Tile)

register_helper(NAME TileMovement
                SOURCES "TileMovement.hpp"
                DEPENDENCIES sfml-graphics Board)

register_helper(NAME ShipPlacement
                SOURCES "ShipPlacement.hpp"
                DEPENDENCIES sfml-graphics Board TileMovement)

register_helper(NAME FiringMechanism
                SOURCES "FiringMechanism.hpp"
                DEPENDENCIES sfml-graphics Board TileMovement)

register_spike(NAME WindowAndDrawBall
               SOURCES "WindowAndDrawBall.cpp"
               DEPENDENCIES sfml-graphics fmt::fmt spdlog::spdlog)

register_spike(NAME ButtonTest
               SOURCES "ButtonTest.cpp"
               DEPENDENCIES sfml-graphics fmt::fmt spdlog::spdlog
                            Button FileNotFoundException)

register_spike(NAME BoardTest
              SOURCES "Board.cpp" "Board.h"
                      "Tile.cpp" "Tile.h"
                      "TestBoardMain.cpp"
              DEPENDENCIES sfml-graphics)

register_spike(NAME SceneManagerTest
               SOURCES "SceneManagerTest.cpp"
                       "GUI/Scene.hpp"
               DEPENDENCIES sfml-graphics fmt::fmt spdlog::spdlog
                            BadIndexError)

register_spike(NAME BasicBattleship
                SOURCES "BasicBattleship.cpp" "Animation.h" "Animation.cpp"
                "State.hpp"
                DEPENDENCIES sfml-graphics Board TileMovement ShipPlacement FiringMechanism)

register_spike(NAME BasicBattleshipTests
                SOURCES "BasicBattleshipTests.cpp" 
                "Animation.h" "Animation.cpp" "Tests.h" "Tests.cpp"
                DEPENDENCIES sfml-graphics Board TileMovement ShipPlacement FiringMechanism)