#pragma once

#include <iostream>

class Point
{
public:

  double x;
  double y;

public:

  Point() {};

  Point(double _x, double _y)
  {
    x = _x;
    y = _y;
  }

  // возврат координаты "x" у точки
  double getX()
  {
    return x;
  }

  // возврат координаты "y" у точки
  double getY()
  {
    return y;
  }
};
