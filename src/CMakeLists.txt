add_definitions(-DCURVE_EXPORTS)
add_library(Curve SHARED Curve.h Point.cpp Point.h Line.cpp Line.h Circle.cpp Circle.h)
install(TARGETS Curve DESTINATION ${CMAKE_INSTALL_PREFIX})
