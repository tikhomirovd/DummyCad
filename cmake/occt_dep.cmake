# Created on: August 9, 2017
# Created by: Artem ZHIDKOV
# Summary: Configure OCCT 3rd parties
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


# OCCT dependencies descriptions
set(3RDPARTY_FREETYPE_DIR_DESCRIPTION           "Path to Freetype library")
set(3RDPARTY_FREEIMAGE_DIR_DESCRIPTION          "Path to FreeImage library")
set(3RDPARTY_TCL_DIR_DESCRIPTION                "Path to Tcl library")
set(3RDPARTY_TK_DIR_DESCRIPTION                 "Path to Tk library")


if(NOT 3RDPARTY_FREETYPE_DIR)
  set(3RDPARTY_FREETYPE_DIR "" CACHE PATH "${3RDPARTY_FREETYPE_DIR_DESCRIPTION}")
  if(3RDPARTY_DIR)
    file(GLOB loc_FT_DIR "${3RDPARTY_DIR}/freetype*")
    if(NOT loc_FT_DIR)
      set(loc_FT_DIR "3RDPARTY_FREETYPE-NOTFOUND")
    endif()
    # update variables
    set(3RDPARTY_FREETYPE_DIR "${loc_FT_DIR}" CACHE PATH "${3RDPARTY_FREETYPE_DIR_DESCRIPTION}" FORCE)
  endif()
endif()
if(NOT ("${3RDPARTY_FREETYPE_DIR}" STREQUAL ""))
  set(CMAKE_PREFIX_PATH "${3RDPARTY_FREETYPE_DIR}" "${CMAKE_PREFIX_PATH}")
endif()
find_package(Freetype 2.5.5 REQUIRED MODULE)


if(NOT 3RDPARTY_TCL_DIR)
  set(3RDPARTY_TCL_DIR "" CACHE PATH "${3RDPARTY_TCL_DIR_DESCRIPTION}")
  set(3RDPARTY_TK_DIR  "" CACHE PATH "${3RDPARTY_TK_DIR_DESCRIPTION}")
  if(3RDPARTY_DIR)
    file(GLOB loc_TCL_DIR "${3RDPARTY_DIR}/tcltk*")
    if(NOT loc_TCL_DIR)
      set(loc_TCL_DIR "3RDPARTY_TCLTK-NOTFOUND")
    endif()
    # update variables
    set(3RDPARTY_TCL_DIR "${loc_TCL_DIR}" CACHE PATH "${3RDPARTY_TCL_DIR_DESCRIPTION}" FORCE)
    set(3RDPARTY_TK_DIR  "${loc_TCL_DIR}" CACHE PATH "${3RDPARTY_TK_DIR_DESCRIPTION}" FORCE)
  endif()
endif()
if(NOT ("${3RDPARTY_TCL_DIR}" STREQUAL ""))
  set(CMAKE_PREFIX_PATH "${3RDPARTY_TCL_DIR}" "${CMAKE_PREFIX_PATH}")
endif()
find_package(TCL 8.6 REQUIRED MODULE)


if(NOT 3RDPARTY_FREEIMAGE_DIR)
  set(3RDPARTY_FREEIMAGE_DIR "" CACHE PATH "${3RDPARTY_FREEIMAGE_DIR_DESCRIPTION}")
  if(3RDPARTY_DIR)
    file(GLOB loc_FIMG_DIR "${3RDPARTY_DIR}/freeimage*")
    if(NOT loc_FIMG_DIR)
      set(loc_FIMG_DIR "3RDPARTY_FREEIMAGE-NOTFOUND")
    endif()
    # update variables
    set(3RDPARTY_FREEIMAGE_DIR "${loc_FIMG_DIR}" CACHE PATH "${3RDPARTY_FREEIMAGE_DIR_DESCRIPTION}" FORCE)
  endif()
endif()
