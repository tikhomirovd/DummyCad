#pragma once

// Includes from STL.
#include <vector>
#include <memory>

// Includes from Core.
#include <Export.h>
#include <Point.h>
#include <Curve.h>
#include <Vector.h>

/**
Включение классов : линия и круг.
*/
class Line;
class Circle;

///  Перечисление для всех случаев кривых
/// \param NO_INTERSECTION   Нет пересечения кривых - нет решения.
/// \param COINCIDENCE       Полное совпадение кривых.
/// \param SOLUTION          Есть пересечение кривых - решение найдено.
/// \param UNSUPPORTED_CURVE Кривая задана некорректно/ нет случая обработки заданной кривой.
enum CalculatoreType 
{ 
NO_INTERSECTION, 
COINCIDENCE,
SOLUTION, 
UNSUPPORTED_CURVE,
};

struct CalculationResult 
{
  /// Конструктор, у которого тип по умолчанию - NO_INTERSECTION.
  CalculationResult() : type(NO_INTERSECTION) {};

  std::vector<Point> solution; ///< param solution Вектор точек - найденные решения.
  CalculatoreType type;        ///< param type     Параметр, показывающий состояние из перечисления.
};

/// Общий интерфейс для нахождения точек пересечения
class Intersections
{

public:

  /// Метод поиска точкек пересечения, принимающий указатели на тип кривой
  Intersection_EXPORT std::shared_ptr<CalculationResult> Intersection(std::shared_ptr<Curve> ptr1, std::shared_ptr<Curve> ptr2);

protected:

  /// Solves line / line case.
  Intersection_EXPORT std::shared_ptr<CalculationResult> SolveLineLine(std::shared_ptr<Line> ptr1, std::shared_ptr<Line> ptr2);

  /// Solves circle / circle case.
  Intersection_EXPORT std::shared_ptr<CalculationResult> SolveCircleCircle(std::shared_ptr<Circle> ptr1, std::shared_ptr<Circle> ptr2);

  /// Solves circle / line.
  Intersection_EXPORT std::shared_ptr<CalculationResult> SolveCircleLine(std::shared_ptr<Circle> ptr1, std::shared_ptr<Line> ptr2);
};
