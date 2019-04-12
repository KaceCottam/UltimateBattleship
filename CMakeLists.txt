cmake_minimum_required(VERSION 3.8)

option(BUILD_SOURCE "Build the source files" ON)
option(BUILD_TESTS "Build the test files" ON)
option(BUILD_SPIKE "Build the spike files (files made for testing code)" ON)

set(CW_BIN ${CMAKE_SOURCE_DIR}/bin) # The binary output directory
set(CW_INCLUDE ${CMAKE_SOURCE_DIR}/include) # The directory where includes are placed

project(UltimateBattleship LANGUAGES C CXX VERSION 0.0.1) # Setup project

# Defining all of the files
set(
  UB_SOURCE_FILES src/main.cpp
) 


add_executable(UltimateBattleship ${UB_SOURCE_FILES}) # Tell CMake to build to an executable

# Include the include/ folder
target_include_directories(UltimateBattleship PRIVATE ${CW_INCLUDE})

if(BUILD_SPIKE)
  add_subdirectory(spike)
endif()