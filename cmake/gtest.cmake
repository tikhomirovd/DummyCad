# Created on: April 15, 2019
# Created by: Artem ZHIDKOV
# Summary: Google Test engine configuration


set(GTEST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/googletest-1.8.1" CACHE PATH "GoogleTest root directory")
find_package(GTest 1.8)

if(GTEST_FOUND)
  message(STATUS "Google Test library FOUND")
  enable_testing()

  set(_gtest_release "")
  set(_gtest_debug "")
  if(EXISTS "${GTEST_MAIN_LIBRARY}")
    get_filename_component(_gtest_path "${GTEST_MAIN_LIBRARY}" DIRECTORY)
    set(_gtest_release "${_gtest_path}")
    set(_gtest_debug "${_gtest_path}")
  endif()
  if(EXISTS "${GTEST_MAIN_LIBRARY_DEBUG}")
    get_filename_component(_gtest_path "${GTEST_MAIN_LIBRARY_DEBUG}" DIRECTORY)
    set(_gtest_debug "${_gtest_path}")
  endif()

  add_test_environment("Release" "${_gtest_release}")
  add_test_environment("Debug" "${_gtest_debug}")
else()
  message(WARNING "GTest 1.8 has not been found. Please set GTEST_ROOT to be able to run unit tests.")
endif()
