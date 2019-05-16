cmake_minimum_required(VERSION 3.0)
project(DummyCAD)

set(CMAKE_CXX_STANDARD 14)
# Always include current directory
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# Path where to find additional CMake sources
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(macros)
include(occt)
include(gtest)
include(doc)

add_subdirectory(src)
add_subdirectory(test)
