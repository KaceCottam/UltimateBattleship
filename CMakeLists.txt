cmake_minimum_required(VERSION 3.8)

option(CW_SFML_TYPE_VS "Using SFML with Visual Studio 14" OFF)
option(CW_SFML_TYPE_GCC "Using SFML with GCC/minGW" ON)
if(CW_SFML_TYPE_VS)
  set(CW_SFML_TYPE "VS")
  set(CW_SFML_LIB_PRE "")
  set(CW_SFML_LIB_SUF ".lib")
elseif(CW_SFML_TYPE_GCC)
  set(CW_SFML_TYPE "GCC")
  set(CW_SFML_LIB_PRE "lib")
  set(CW_SFML_LIB_SUF ".a")
#else()
  # Using manually set
endif()

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_FIND_LIBRARY_PREFIXES ${CW_SFML_LIB_PRE})
set(CMAKE_FIND_LIBRARY_SUFFIXES ${CW_SFML_LIB_SUF})

set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/SFML_${CW_SFML_TYPE}/lib/cmake/SFML")
set(SFML_INCLUDE "${CMAKE_SOURCE_DIR}/lib/SFML/include")
find_package(SFML 2.5 REQUIRED system window graphics network audio)

option(BUILD_SOURCE "Build the source files" OFF)
option(BUILD_TESTS "Build the test files" ON)
option(BUILD_SPIKE "Build the spike files (files made for testing code snippets)" ON)

set(CW_BIN ${CMAKE_SOURCE_DIR}/bin) # The binary output directory

if(BUILD_SOURCE)
  project(UltimateBattleship LANGUAGES C CXX VERSION 0.0.1) # Setup project
  # UltimateBattleship project related variables will be prefixed by 'UB_'

  # Defining all of the files
  set(
    UB_SOURCE_FILES src/main.cpp
  ) 


  add_executable(UltimateBattleship ${UB_SOURCE_FILES}) # Tell CMake to build to an executable

  # Link UltimateBattleship with various libraries
  target_link_libraries(UltimateBattleship sfml-graphics)
endif()

if(BUILD_SPIKE)
  add_subdirectory(spike)
endif()