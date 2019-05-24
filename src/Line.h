#pragma once

#include <Export.h>
#include <Curve.h>
#include <Vector.h>
#include <Point.h>
/// класс линия - задается точкой и направлением
class Line : public Curve
{
public:
  Line(double x, double y, double _dot1, double _dot2) : Curve(x, y) 
  {
    dot1 = _dot1;
    dot2 = _dot2;
  };

  Intersection_EXPORT virtual Point PointCalcul(double t) const override;

  Intersection_EXPORT virtual Vector Gradient(double t) const  override;

  bool ClosedCurve() const override 
  {
    return false;
  }

  const Vector& getDirection() const
  {
    return Vector(dot1, dot2);
  }

protected:
  double dot1, dot2;
};
