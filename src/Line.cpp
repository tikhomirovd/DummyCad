#include <Line.h>

Point Line::PointCalcul(double t) const
{
  double x = point.getX() - myDirection.getX() * t;
  double y = point.getY() - myDirection.getY() * t;
  return Point(x, y);
}

Vector Line::Gradient(double t) const
{
  return myDirection;
}
