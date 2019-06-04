# Created on: April 15, 2019
# Created by: Artem ZHIDKOV
# Summary: Sample project solving square equation

set(LIBRARY_NAME "Intersection")

set(LIBRARY_HEADERS
    Defines.h
    Curve.h
	TVector.h
	TPoint.h
	Line.h
	Circle.h
	InterPoints.h
)

set(LIBRARY_SOURCES
    Curve.cpp
    main.cpp
	TPoint.cpp
	TVector.cpp
	Line.cpp
	Circle.cpp
	InterPoints.cpp
)

add_definitions(-DINTERSECTION_EXPORTS)
#add_library(${LIBRARY_NAME} SHARED ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})
add_executable(${LIBRARY_NAME} ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})
install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})

foreach(_mode ${CMAKE_CONFIGURATION_TYPES})
  add_test_environment("${_mode}" "${CMAKE_CURRENT_BINARY_DIR}/${_mode}")
endforeach()

