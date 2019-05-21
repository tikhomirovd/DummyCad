#pragma once

#include <vector>
#include <memory>

#include <Export.h>
#include <Point.h>
#include <Curve.h>
#include <Vector.h>

class Line;
class Circle;

enum CalculatoreType { 
NO_INTERSECTION, 
COINCIDENCE, 
NULL_POINTER, 
SOLUTION, 
UNSUPPORTED_CURVE};

struct CalculationResult {
  CalculationResult() : type(NO_INTERSECTION){};
  std::vector<Point> solution;
  CalculatoreType type;
};
//общий интерфейс для нахождения точек пересечения
class Intersections
{

public:
  //метод поиска точкек пересечения, принимающий указатели на тип кривой
  Intersection_EXPORT CalculationResult* Intersection(std::shared_ptr<Curve> ptr1, std::shared_ptr<Curve> ptr2);

protected:
  // Solves line / line case.
  Intersection_EXPORT CalculationResult* SolveLineLine(std::shared_ptr<Line> ptr1, std::shared_ptr<Line> ptr2);
  // Solves circle / circle case.
  Intersection_EXPORT CalculationResult* SolveCircleCircle(std::shared_ptr<Circle> ptr1, std::shared_ptr<Circle> ptr2);
  // Solves circle / line.
  Intersection_EXPORT CalculationResult* SolveCircleLine(std::shared_ptr<Circle> ptr1, std::shared_ptr<Line> ptr2);
};
