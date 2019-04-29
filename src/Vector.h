#pragma once

#include <iostream>

class Vector
{
private:
  double x;
  double y;

public:
  Vector(double a, double b)
  {
    x = a;
    y = b;
  }
  /*Vector (Point a, Point b)
  {
    return Vector (a,b);
  } */
  // получение координаты x вектора
  double getX() const
  {
    return x;
  }
  // получение координаты y вектора
  double getY() const
  {
    return y;
  }

  // Get vector's squared norm.
  double getSquaredNorm()
  {
    return x * x + y * y;
  }

  // Get vector's  norm.
  double getNorm()
  {
    return sqrt(getSquaredNorm());
  }

  // Calculates dot product of me and other vector.
  double getDot(const Vector& other)
  {
    return x * other.getX() + y * other.getY();
  }

  // Multiply me by scalar.
  Vector Multiply(const double scalar)
  {
    return Vector(x * scalar, y * scalar);
  }

  // Normalizes vector.
  Vector Normalize()
  {
    const double length = getNorm();
    return Multiply(1.0 / length);
  }
};
