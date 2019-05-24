#pragma once

class Point
{
protected:

  double x;
  double y;

public:

  Point() {};

  Point(double _x,
  double _y) {
    x = _x;
    y = _y;
  }

  bool operator == (Point p) 
  {
    return x==p.getX() && y==p.getY();
  }
  /// возврат координаты "x" у точки
  double getX() const 
  {
    return x;
  }
  /// возврат координаты "y" у точки
  double getY() const 
  {
    return y;
  }
};
