#include <Line.h>
// класс линия - задается точкой и направлением
  Point Line::PointCalcul(double t) const {
  double x = point.getX() - dot1*t;
  double y = point.getY() - dot2*t;
  return Point(x, y);
}

  Vector Line::Gradient(double t) const {
    return Vector(dot1, dot2);
}
