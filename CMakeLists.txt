cmake_minimum_required(VERSION 3.0)
project(curve)

set(CMAKE_CXX_STANDARD 14)
# Always include current directory
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)


add_subdirectory(src)


set(GTEST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/googletest-1.8.1" CACHE PATH "GoogleTest root directory")
find_package(GTest 1.8)

if(GTEST_FOUND)
  message(STATUS "Google Test library FOUND")
  enable_testing()
else()
  message(WARNING "GTest 1.8 has not been found. Please set GTEST_ROOT to be able to run unit tests.")
endif()

add_subdirectory(test)


add_executable(CurveExec main.cpp)
target_include_directories(CurveExec PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(CurveExec Curve)
install(TARGETS CurveExec DESTINATION ${CMAKE_INSTALL_PREFIX})
