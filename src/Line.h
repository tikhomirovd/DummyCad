#pragma once

#include <Export.h>
#include <Curve.h>
#include <Vector.h>
#include <Point.h>
/// ����� ����� - �������� ������ � ������������
class Line : public Curve
{
public:
  Line(double x, double y, Vector direction) : Curve(x, y) 
  {
    direction = Vector (dot1, dot2);
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
