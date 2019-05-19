#pragma once
#include <Vector.h>
#include <Point.h>

// класс кривой - получение точки на ней и реализация методов
class Curve
{
protected:

  Point point;

public:
  Point getCurvePoint() const  {
    return point;
  }

  // координата в зависимости от параметра
  virtual Point PointCalcul(double t) = 0;

  // касательная к кривой
  virtual Vector Gradient(double t) = 0;

  // является ли кривая замкнутой
  virtual bool ClosedCurve() = 0;

protected:
  Curve(double x, double y) : point(x, y) {
  }
};
