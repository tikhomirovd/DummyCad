cmake_minimum_required(VERSION 3.13)
project(curve)

set(CMAKE_CXX_STANDARD 14)

add_executable(curve main.cpp Curve.h Point.cpp Point.h Line.cpp Line.h Circle.cpp Circle.h)