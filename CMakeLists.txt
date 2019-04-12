cmake_minimum_required(VERSION 3.8)

option(BUILD_SOURCE "Build the source files" ON)
option(BUILD_TESTS "Build the test files" ON)

set(CW_BIN ${CMAKE_SOURCE_DIR}/bin) # The binary output directory

add_subdirectory(src)