#pragma once

#include <Vector.h>
#include <Point.h>

// класс кривой - получение точки на ней и реализация методов
class Curve
{
protected:

  Point point;

  Curve(double x, double y) : point(x, y) {
  }

public:
  const Point& getCurvePoint() const {
    return point;
  }
  // координата в зависимости от параметра
  virtual Point PointCalcul(double t) const = 0;
  // касательная к кривой
  virtual Vector Gradient(double t) const = 0;
  // является ли кривая замкнутой
  virtual bool ClosedCurve() const = 0;

};
