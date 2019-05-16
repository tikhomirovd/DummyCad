# Created on: June 2, 2017
# Created by: Artem ZHIDKOV
# Summary: Configure OCCT variables
#
# Copyright (c) 2017-2018 OPEN CASCADE SAS
# 
# This file is part of commercial software by OPEN CASCADE SAS. 
# 
# This software is furnished in accordance with the terms and conditions 
# of the contract and with the inclusion of this copyright notice. 
# This software or any other copy thereof may not be provided or otherwise 
# be made available to any third party. 
# No ownership title to the software is transferred hereby. 
# 
# OPEN CASCADE SAS makes no representation or warranties with respect to the 
# performance of this software, and specifically disclaims any responsibility 
# for any damages, special or consequential, connected with its use. 

# OCCT required version
set(3RDPARTY_OCCT_VERSION "7.3.0" CACHE STRING "Required version of OpenCASCADE Technology")

if(NOT "${3RDPARTY_OCCT_DIR}")
  # create corresponding 3rd party variable
  set(3RDPARTY_OCCT_DIR "" CACHE PATH "Path to OpenCASCADE Technology")

  if(3RDPARTY_DIR)
    # search OCCT config file in the third parties directory
    set (loc_OCCT_CONFIG)
    file(GLOB_RECURSE loc_OCCT_CONFIG "${3RDPARTY_DIR}/*/OpenCASCADEConfig.cmake")
    if(NOT loc_OCCT_CONFIG)
      set(loc_OCCT_CONFIG "3RDPARTY_OCCT_CONFIG_FILE-NOTFOUND")
      set(3RDPARTY_OCCT_CONFIG_FILE "${loc_OCCT_CONFIG}" CACHE FILEPATH "Full path to OpenCASCADEConfig.cmake" FORCE)
    endif()

    if (3RDPARTY_OCCT_CONFIG_FILE)
      list (APPEND loc_OCCT_CONFIG "${3RDPARTY_OCCT_CONFIG_FILE}")
    endif()

    foreach(loc_CONFIG ${loc_OCCT_CONFIG})
      get_filename_component(loc_OCCT_DIR "${loc_CONFIG}" DIRECTORY)
      set(CMAKE_PREFIX_PATH "${loc_OCCT_DIR}" "${CMAKE_PREFIX_PATH}")
    endforeach()
  endif()

endif()

if(NOT EXISTS "${3RDPARTY_OCCT_DIR}")
  message(FATAL_ERROR "3RDPARTY_OCCT_DIR variable is NOT specified")
endif()

if(NOT ("${3RDPARTY_OCCT_DIR_PREV}" STREQUAL "${3RDPARTY_OCCT_DIR}"))
  # discard previously stored OCCT variables
  set(OpenCASCADE_ALREADY_INCLUDED 0)
  set(OpenCASCADE_DIR "" CACHE PATH "" FORCE)
  set(3RDPARTY_OCCT_DIR_PREV "${3RDPARTY_OCCT_DIR}" CACHE INTERNAL "Store previous value of OCCT root directory")
endif()

if(3RDPARTY_OCCT_DIR)
  # find OCCT required 3rd-parties
  include(occt_dep)
  # set directory to find OpenCASCADE
  set(CMAKE_PREFIX_PATH "${3RDPARTY_OCCT_DIR}" "${CMAKE_PREFIX_PATH}")
endif()

find_package(OpenCASCADE ${3RDPARTY_OCCT_VERSION} CONFIG REQUIRED)
if(${OpenCASCADE_FOUND})
  # hide OpenCASCADE_DIR variable
  get_property(docString CACHE OpenCASCADE_DIR PROPERTY HELPSTRING)
  set(OpenCASCADE_DIR "${OpenCASCADE_DIR}" CACHE INTERNAL "${docString}" FORCE)

  set(3RDPARTY_OCCT_DIR "${OpenCASCADE_INSTALL_PREFIX}" CACHE PATH "Path to OpenCASCADE Technology" FORCE)

  # change absolute paths of OCCT 3rd parties by native
  fix_occt_3rdparties("Freetype;FreeImage;Tcl;Tk")

  # update test environment variables
  foreach(_mode ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${_mode}" _mode_uc)

    get_property(_OCCT_TKERNEL TARGET TKernel PROPERTY IMPORTED_LOCATION_${_mode_uc})
    if(NOT EXISTS "${_OCCT_TKERNEL}")
      get_property(_OCCT_TKERNEL TARGET TKernel PROPERTY IMPORTED_LOCATION_RELEASE)
    endif()
    if(EXISTS  "${_OCCT_TKERNEL}")
      get_filename_component(_OCCT_PATH "${_OCCT_TKERNEL}" DIRECTORY)
      add_test_environment(${_mode} ${_OCCT_PATH})
    endif()

    # OCCT 3rd parties paths
    if(EXISTS "${3RDPARTY_FREETYPE_DIR}")
      add_test_environment(${_mode} "${3RDPARTY_FREETYPE_DIR}/bin")
      add_test_environment(${_mode} "${3RDPARTY_FREETYPE_DIR}/lib")
    endif()
    if(EXISTS "${3RDPARTY_FREEIMAGE_DIR}")
      add_test_environment(${_mode} "${3RDPARTY_FREEIMAGE_DIR}/bin")
      add_test_environment(${_mode} "${3RDPARTY_FREEIMAGE_DIR}/lib")
    endif()
    if(EXISTS "${3RDPARTY_TCL_DIR}")
      add_test_environment(${_mode} "${3RDPARTY_TCL_DIR}/bin")
      add_test_environment(${_mode} "${3RDPARTY_TCL_DIR}/lib")
    endif()
  endforeach()

  message(STATUS "OpenCASCADE Technology version ${OpenCASCADE_VERSION} FOUND")
else()
  unset(3RDPARTY_OCCT_DIR_DEFINED CACHE)
endif()
