cmake_minimum_required(VERSION 3.8)

# Enable options by typing `cmake -B build -D<option name>=<value> ...` 
#  in the root directory
option(BUILD_SOURCE "Build the source files" OFF)
option(BUILD_TESTS "Build the test files" ON)
option(BUILD_SPIKE "Build the spike files (files made for testing code snippets)"
       ON)

set(CW_BIN ${CMAKE_SOURCE_DIR}/bin) # The binary output directory

project(UltimateBattleship LANGUAGES C CXX VERSION 0.0.1) # Setup project
# UltimateBattleship project related variables will be prefixed by 'UB_'

# include SFML. Must be done here so that everything links correctly.
set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/SFML/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED graphics network audio)

# add fmt library
add_subdirectory(lib/fmt)
# add spdlog library
add_subdirectory(lib/spdlog)

if(BUILD_SOURCE)
  # Defining all of the files
  set(
    UB_SOURCE_FILES src/main.cpp
  )
  add_executable(UltimateBattleship ${UB_SOURCE_FILES}) # Tell CMake to build to
                                                        # an executable

  # Link UltimateBattleship with various libraries
  target_link_libraries(UltimateBattleship sfml-graphics)
endif()

if(BUILD_SPIKE)
  add_subdirectory(spike)
endif()