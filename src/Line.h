#pragma once

// Includes from STL.
#include <stdexcept>

// Includes from Core.
#include <Export.h>
#include <Curve.h>
#include <Vector.h>
#include <Point.h>

const double EPS_NORM = 1.0e-7;

/// Класс линия - задается точкой и направлением.
class Line : public Curve
{
public:

  /// \param x         Координата x точки.
  /// \param y         Координата y точки.
  /// \param direction Вектор направления линии.
  Line(double x, double y, Vector direction)
  : Curve(x, y),
    myDirection(direction)
  {
    /// Исключение генерируется приситуации с нулевым направлением.
    if (myDirection.getSquaredNorm() < EPS_NORM * EPS_NORM)
    {
      throw std::invalid_argument("Invalid direction");
    }
  }

  /// Метод, который возвращает точку в зависимости от параметра.
  Intersection_EXPORT virtual Point PointCalcul(double t) const override;

  /// Метод, который определяет вектор касательной к линии.
  Intersection_EXPORT virtual Vector Gradient(double t) const  override;

  /// Метод определяет замкнутость линии.
  bool ClosedCurve() const override
  {
    return false;
  }

  /// Метод возвращает направляющий вектор линии.
  const Vector& getDirection() const
  {
    return myDirection;
  }

protected:

  /// Объявлен направляющий вектор.
  Vector myDirection;
};
