#include <math.h>

#include <Circle.h>
#include <Curve.h>
#include <Vector.h>
#include <Point.h>

  Vector Circle::Gradient(double t) const {
    double x = Radius * (-sin(t));
    double y = Radius * cos(t);
    return Vector(x, y);
  } 

  Point Circle::PointCalcul(double t) const {
    return Point(Radius * cos(t), Radius * sin(t));
}
