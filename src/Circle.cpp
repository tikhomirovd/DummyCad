﻿#pragma once

#include <iostream>
#include <math.h>

#include <Curve.h>
#include <Vector.h>
#include <Point.h>

class Circle : public Curve
{
public:
  Circle(double x,
    double y,
    double radius) 
    : Curve(x, y)
  {
    Radius = radius;
  }

  double getRadius()
  {
    return Radius;
  }

  bool ClosedCurve() override
  {
    return true;
  }

  Vector Gradient(double t)
  {
    double x = Radius * (-sin(t));
    double y = Radius * cos(t);
    return Vector(x, y);
  }

// расчет точки в зависимости от параметра
  Point PointCalcul(double t)
  {
    return Point(Radius * cos(t), Radius * sin(t));
  }

protected:
  double Radius;
};
