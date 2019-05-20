#pragma once

#include <Curve.h>
#include <Vector.h>
#include <Point.h>

// класс линия - задается точкой и направлением
class Line : public Curve
{
public:
  Line(double x, double y, double _dot1, double _dot2) : Curve(x, y) {
    dot1 = _dot1;
    dot2 = _dot2;
};

  virtual Point PointCalcul(double t) override;

  virtual Vector Gradient(double t)  override;

  bool ClosedCurve() override
  {
    return false;
  }

  double getDot1() const
  {
    return dot1;
  }

  double getDot2() const
  {
    return dot2;
  }

protected:
  double dot1, dot2;
};
