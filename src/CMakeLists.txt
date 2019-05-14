# Created on: April 18, 2019
# Created by: Julia Guskova
# Summary: Curves intersection library

set(LIBRARY_NAME "Intersection")

set(LIBRARY_HEADERS
    Export.h
    Curve.h
    Intersection.h
    Point.h
    Vector.h
)

set(LIBRARY_SOURCES
    Circle.cpp
    Intersection.cpp
    Straight.cpp
)

add_library(${LIBRARY_NAME} SHARED ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})
install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})

foreach(_mode ${CMAKE_CONFIGURATION_TYPES})
  add_test_environment("${_mode}" "${CMAKE_CURRENT_BINARY_DIR}/${_mode}")
endforeach()
