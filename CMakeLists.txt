cmake_minimum_required(VERSION 3.8)

option(BUILD_SOURCE "Build the source files" ON)
option(BUILD_TESTS "Build the test files" ON)
option(BUILD_SPIKE "Build the spike files (files made for testing code)" ON)

set(CW_BIN ${CMAKE_SOURCE_DIR}/bin) # The binary output directory
set(CW_INCLUDE ${CMAKE_SOURCE_DIR}/include) # The directory where includes are placed

project(UltimateBattleship LANGUAGES C CXX VERSION 0.0.1)

target_link_directories(UltimateBattleship ${CW_INCLUDE})

if(BUILD_SPIKE)
  add_subdirectory(spike)
endif()