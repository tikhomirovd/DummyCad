add_definitions(-DCURVE_EXPORTS)
add_library(Curve SHARED Curve.h Point.cpp Point.h Line.cpp Line.h Circle.cpp Circle.h Intersection.cpp Intersection.h )
install(TARGETS Curve DESTINATION ${CMAKE_INSTALL_PREFIX})

foreach(_mode ${CMAKE_CONFIGURATION_TYPES})
  add_test_environment("${_mode}" "${CMAKE_CURRENT_BINARY_DIR}/${_mode}")
endforeach()

include_directories("/home/dimas/OpenCascade7.3.0/include/opencascade")
