# Created on: April 23, 2019
# Created by: Artem ZHIDKOV
# Summary: Documentation configuration


# Enable building of the documentation
set(ENABLE_DOCUMENTATION False CACHE BOOL "Enable/Disable building documentation")

if(NOT "${ENABLE_DOCUMENTATION}")
  message(STATUS "Documentation disabled.")
  return()
endif()

if(NOT "${3RDPARTY_DOXYGEN_DIR}" OR NOT "${3RDPARTY_GRAPHVIZ_DIR}")
  # create corresponding 3rd party variable
  set(3RDPARTY_DOXYGEN_DIR "" CACHE PATH "Path to Doxygen")
  set(3RDPARTY_GRAPHVIZ_DIR "" CACHE PATH "Path to Graphviz")

  if(3RDPARTY_DIR)
    # search Doxygen and Graphviz directories
    set(loc_DOCS "DOXYGEN" "GRAPHVIZ")
    foreach(doc ${loc_DOCS})
      file(GLOB loc_FOUND "${3RDPARTY_DIR}/${doc}*")
      foreach(p ${loc_FOUND})
        if(IS_DIRECTORY "${p}")
          set(CMAKE_PREFIX_PATH "${p}" "${CMAKE_PREFIX_PATH}")
        endif()
      endforeach()
    endforeach()
  endif()

else()
  set(CMAKE_PREFIX_PATH "${3RDPARTY_DOXYGEN_DIR}" "${3RDPARTY_GRAPHVIZ_DIR}" "${CMAKE_PREFIX_PATH}")
endif()

set(DOXYGEN_EXECUTABLE_DIR "" CACHE PATH "Path to Doxygen executable")
set(DOXYGEN_GRAPHVIZ_DIR "" CACHE PATH "Path to GraphViz")

if(EXISTS "${DOXYGEN_EXECUTABLE_DIR}")
  set(CMAKE_PREFIX_PATH "${DOXYGEN_EXECUTABLE_DIR}" "${CMAKE_PREFIX_PATH}")
endif()

if(EXISTS "${DOXYGEN_GRAPHVIZ_DIR}")
  set(CMAKE_PREFIX_PATH "${DOXYGEN_GRAPHVIZ_DIR}" "${CMAKE_PREFIX_PATH}")
endif()

set(DOXYGEN_MINIMAL_VERSION 1.8.9)
find_package(Doxygen ${DOXYGEN_MINIMAL_VERSION})
if(${DOXYGEN_FOUND} AND ${DOXYGEN_DOT_FOUND})
  message(STATUS "Doxygen version ${DOXYGEN_VERSION} FOUND")

  # setup input directory for documentation template
  set(PROJECT_DOC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dox")
  # set relative path to documentation directory
  set(INSTALL_DOC_RELATIVE "${CMAKE_INSTALL_PREFIX}/doc")

  # setup Doxygen
  set(DOXYFILE_IN  ${PROJECT_DOC_DIR}/Doxyfile.in)
  set(DOXYFILE     ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  set(DOXY_INPUT   ${CMAKE_SOURCE_DIR})
  set(DOXY_OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/doc)
  set(DOXY_IMGPATH ${PROJECT_DOC_DIR}/images)

  configure_file(${DOXYFILE_IN} ${DOXYFILE} @ONLY)

  add_custom_target(Documentation ALL
                    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
                    SOURCES ${DOXYFILE}
                    VERBATIM)
  install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/html"
          DESTINATION ${INSTALL_DOC_RELATIVE}
          COMPONENT "Documentation")
  install(FILES "${PROJECT_DOC_DIR}/doc.html"
          DESTINATION ${INSTALL_DOC_RELATIVE}
          COMPONENT "Documentation")
  
else()
  message(WARNING "Doxygen ${DOXYGEN_MINIMAL_VERSION} has not been found. Unable to generate documentation")
endif()
