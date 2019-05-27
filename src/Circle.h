#pragma once

#include <Export.h>
#include <Curve.h>
#include <Vector.h>
#include <Point.h>
/// класс задается точкой центра окружности и радиусом
class Circle : public Curve
{
public:
  Circle(double x, double y, double radius)
    : Curve(x, y), 
      Radius (radius)
  {
  }

  Intersection_EXPORT virtual Point PointCalcul(double t) const override;

  Intersection_EXPORT virtual Vector Gradient(double t) const override;

  double getRadius() const 
  {
    return Radius;
  }

  bool ClosedCurve() const override 
  {
    return true;
  }

protected:
  double Radius;
};
