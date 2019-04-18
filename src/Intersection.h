#pragma once
#include <vector>
#include <memory>

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
	vector<Points> Intersection(shared_ptr<Curve> ptr1, shared_ptr<Curve> ptr2);
};