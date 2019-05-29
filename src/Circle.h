#pragma once

// Includes from Core.
#include <Export.h>
#include <Curve.h>
#include <Vector.h>
#include <Point.h>

/// Класс задается точкой центра окружности и радиусом.
class Circle : public Curve
{
public:

  /// \param x      Координата x точки.
  /// \param y      Координата y точки.
  /// \param radius Радиус заданной окружности.
  Circle(double x,
         double y,
         double radius)
  : Curve(x, y), 
    Radius (radius)
  {}

  /// Виртуальный переопределенный константный метод, который возвращает точку в зависимости от параметра.
  Intersection_EXPORT virtual Point PointCalcul(double t) const override;

  /// Виртуальный переопределенный константный метод, который определяет вектор касательной к кругу.
  Intersection_EXPORT virtual Vector Gradient(double t) const override;

  /// Метод получает радиус.
  double getRadius() const
  {
    return Radius;
  }

  /// Метод определяет замкнутость круга.
  bool ClosedCurve() const override 
  {
    return true;
  }

protected:

  /// Задается радиус.
  double Radius;
};
