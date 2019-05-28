#include <Line.h>

/// Реализация метода определения точки в зависимости от параметра.
/// \param x Расчет координаты точки x в зависимости от параметра.
/// \param y Расчет координаты точки y в зависимости от параметра.
Point Line::PointCalcul(double t) const
{
  double x = point.getX() - myDirection.getX() * t;
  double y = point.getY() - myDirection.getY() * t;
  return Point(x, y);
}

/// Реализация метода определения вектора касательной к линии.
Vector Line::Gradient(double t) const
{
  return myDirection;
}
