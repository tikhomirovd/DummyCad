#pragma once

#include <Vector.h>
#include <Point.h>

/// Класс кривой - получение точки на ней и реализация методов.
class Curve
{
public:

  /// Метод получает точку на заданной кривой.
  const Point& getCurvePoint() const
  {
    return point;
  }

  /// Координата в зависимости от параметра.
  virtual Point PointCalcul(double t) const = 0;

  /// Касательная к кривой.
  virtual Vector Gradient(double t) const = 0;

  /// Является ли кривая замкнутой.
  virtual bool ClosedCurve() const = 0;

protected:

  /// Создается точка.
  Point point;

  /// Защищенный конструктор - для того, чтобы только наследники могли создать экземпляр класса.
  Curve(double x, double y) : point(x, y)
  {
  }
};
