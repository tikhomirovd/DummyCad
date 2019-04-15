# Created on: April 15, 2019
# Created by: Artem ZHIDKOV
# Summary: Sample project solving square equation

set(LIBRARY_NAME "Equation")

set(LIBRARY_HEADERS
    Defines.h
    Equation.h
)

set(LIBRARY_SOURCES
    Equation.cpp
)

add_definitions(-DEQUATION_EXPORTS)
add_library(${LIBRARY_NAME} SHARED ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})
install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})

foreach(_mode ${CMAKE_CONFIGURATION_TYPES})
  add_test_environment("${_mode}" "${CMAKE_CURRENT_BINARY_DIR}/${_mode}")
endforeach()

