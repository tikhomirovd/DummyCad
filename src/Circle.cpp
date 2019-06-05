// Include self.
#include <Circle.h>

// Includes from STL.
#include <math.h>

// Includes from Core.
#include <Curve.h>
#include <Vector.h>
#include <Point.h>

//=============================================================================
//function : Gradient
//purpose  : находит вектор касательной к кругу
//=============================================================================
Vector Circle::Gradient(double t) const
{
  double x = Radius * (-sin(t));
  double y = Radius * cos(t);
  return Vector(x, y);
}

//=============================================================================
//function : PointCalcul
//purpose  : возвращает точку в зависимости от параметра.
//=============================================================================
Point Circle::PointCalcul(double t) const
{
  return Point(point.getX() + Radius * cos(t),
               point.getY() + Radius * sin(t));
}
