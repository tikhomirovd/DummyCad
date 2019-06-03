# Created on: April 15, 2019
# Created by: Artem ZHIDKOV
# Summary: Google Test engine configuration

if(NOT 3RDPARTY_GOOGLETEST_DIR)
  # create corresponding 3rd party variable
  set(3RDPARTY_GOOGLETEST_DIR "" CACHE PATH "GoogleTest root directory")

  if(3RDPARTY_DIR)
    # search GTest library in the third parties directory
    file(GLOB_RECURSE loc_GTEST_INCLUDE "${3RDPARTY_DIR}/*/gtest.h")
    foreach(loc_INC ${loc_GTEST_INCLUDE})
      string(REGEX MATCH "(gtest/gtest.h)$" loc_INC_FOUND "${loc_INC}")
      if(loc_INC_FOUND)
        set(loc_GTEST_INCLUDE ${loc_INC})
        break()
      endif()
    endforeach()

    if(loc_GTEST_INCLUDE)
      get_filename_component(loc_GTEST_DIR "${loc_GTEST_INCLUDE}" DIRECTORY)
      get_filename_component(loc_GTEST_DIR "${loc_GTEST_DIR}/../.." ABSOLUTE)
      set(3RDPARTY_GOOGLETEST_DIR "${loc_GTEST_DIR}" CACHE PATH "GoogleTest root directory" FORCE)
    endif()
  endif()

endif()

if(3RDPARTY_GOOGLETEST_DIR)
  set(GTEST_ROOT "${3RDPARTY_GOOGLETEST_DIR}")
endif()

set(GTEST_MINIMAL_VERSION 1.8)
find_package(GTest ${GTEST_MINIMAL_VERSION})

if(GTEST_FOUND)
  message(STATUS "Google Test library FOUND")
  enable_testing()
  set(BUILD_TESTING ON)

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
  message(WARNING "GTest ${GTEST_MINIMAL_VERSION} has not been found. Please set 3RDPARTY_GOOGLETEST_DIR to be able to run unit tests.")
endif()
