﻿#pragma once

#include <cmath>

/// Класс задания вектора направления для кривой : получение координат и различные преобразования.
class Vector
{
public:

  /// \param a Координата x точки.
  /// \param b Координата y точки.
  Vector(double a,
         double b)
  {
    x = a;
    y = b;
  }

  /// Получение координаты x вектора.
  double getX() const
  {
    return x;
  }

  /// Получение координаты y вектора.
  double getY() const
  {
    return y;
  }

  /// Get vector's squared norm.
  double getSquaredNorm()
  {
    return x * x + y * y;
  }

  /// Get vector's norm.
  double getNorm()
  {
    return sqrt(getSquaredNorm());
  }

  /// Calculates dot product of me and other vector.
  double getDot(const Vector& other)
  {
    return x * other.getX() + y * other.getY();
  }

  /// Multiply me by scalar.
  Vector Multiply(const double scalar)
  {
    return Vector(x * scalar, y * scalar);
  }

  /// Сумма двух векторов.
  Vector summ(const Vector& p)
  {
    Vector summ = Vector(x + p.getX(), y + p.getY());
    return summ;
  }

  /// Нормализация вектора.
  Vector Normalize()
  {
    const double length = getNorm(); /// \param length   Длина заданного вектора.
    return Multiply(1.0 / length);   /// \param Multiply Результат - нормализованный вектор.
  }

private:

  /**
  Задание координат точки.
  */
  double x;
  double y;
};
