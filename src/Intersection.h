#pragma once

#include <vector>
#include <memory>

#include <Export.h>
#include <Point.h>
#include <Curve.h>
#include <Vector.h>
#include <Line.cpp>
#include <Circle.cpp>

//общий интерфейс для нахождения точек пересечения
class Intersections
{

public:

  //метод поиска точкек пересечения, принимающий указатели на тип кривой
  Intersection_EXPORT std::vector<Point> Intersection(std::shared_ptr<Curve> ptr1, std::shared_ptr<Curve> ptr2);

protected:

  // Solves line / line case.
  Intersection_EXPORT std::vector<Point> SolveLineLine(std::shared_ptr<Line> ptr1, std::shared_ptr<Line> ptr2);

  // Solves circle / circle case.
  Intersection_EXPORT std::vector<Point> SolveCircleCircle(std::shared_ptr<Circle> ptr1, std::shared_ptr<Circle> ptr2);

  // Solves circle / line.
  Intersection_EXPORT std::vector<Point> SolveCircleLine(std::shared_ptr<Circle> ptr1, std::shared_ptr<Line> ptr2);
};
