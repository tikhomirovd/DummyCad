#pragma once

#include <iostream>
#include <math.h>

#include <Curve.h>
#include <Vector.h>
#include <Point.h>

class Circle : public Curve
{
public:
  Circle(double x, double y, double radius)
    : Curve(x, y)
  {
    Radius = radius;
  }

  // расчет точки в зависимости от параметра
  virtual Point PointCalcul(double t) override;

  virtual Vector Gradient(double t) override;

  double getRadius()
  {
    return Radius;
  }

  bool ClosedCurve() override
  {
    return true;
  }

protected:
  double Radius;
};
