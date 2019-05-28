#include <math.h>

#include <Circle.h>
#include <Curve.h>
#include <Vector.h>
#include <Point.h>

/// Реализация метода определения вектора касательной к кругу.
/// \param x Расчет координаты точки x в зависимости от параметра и производной по нему.
/// \param y Расчет координаты точки y в зависимости от параметра и производной по нему.
Vector Circle::Gradient(double t) const
{
  double x = Radius * (-sin(t));
  double y = Radius * cos(t);
  return Vector(x, y);
}
/// Реализация метода определения точки в зависимости от параметра.
Point Circle::PointCalcul(double t) const
{
  return Point(Radius * cos(t), Radius * sin(t));
}
