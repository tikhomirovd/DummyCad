#pragma once

/// Класс задает точку с координатами x и y.
class Point
{
public:

  /**
    Конструктор по умолчанию.
  */
  Point()
  {
    x = 0;
    y = 0;
  };

  /// \param x Координата x точки.
  /// \param y Координата y точки.
  Point(double _x,
    double _y)
  {
    x = _x;
    y = _y;
  }

  /// Переопределение сравнения точек - заданной и текущей.
  bool operator == (Point p)
  {
    return x == p.getX() && y == p.getY();
  }

  /// Возврат координаты "x" у точки.
  double getX() const
  {
    return x;
  }

  /// Возврат координаты "y" у точки.
  double getY() const
  {
    return y;
  }

protected:

  /**
    Задание координат точки.
  */
  double x;
  double y;
};
