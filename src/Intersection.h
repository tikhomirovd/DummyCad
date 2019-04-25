#pragma once
#include <vector>
#include <memory>

#include "Export.h"
#include "Point.h"
#include "Curve.h"
#include "Vector.h"
#include "Straight.cpp"
#include "Circle.cpp"

//общий интерфейс для нахождения точек пересечения
class Intersections
{

public:

  //метод поиска точкек пересечения, принимающий указатели на тип кривой
  Intersection_EXPORT vector<Point> Intersection(shared_ptr<Curve> ptr1, shared_ptr<Curve> ptr2);

protected:

  // Solves line / line case.
  Intersection_EXPORT vector<Point> SolveLineLine(shared_ptr<Straight> ptr1, shared_ptr<Straight> ptr2);

  // Solves circle / circle case.
  Intersection_EXPORT vector<Point> SolveCircleCircle(shared_ptr<Circle> ptr1, shared_ptr<Circle> ptr2);

  // Solves circle / line.
  Intersection_EXPORT vector<Point> SolveCircleLine(shared_ptr<Circle> ptr1, shared_ptr<Straight> ptr2);
};
