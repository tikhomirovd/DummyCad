#include<iostream>
#include <memory>

#include "Curve.h"
#include "Vector.h"
#include "Straight.cpp"
#include "Circle.cpp"
#include "Point.h"
#include "Intersection.h"

int main()
{

	shared_ptr<Curve> straid1 = shared_ptr<Straight>(new Straight(0.0, 0.0, 0.0, 1.0));
	shared_ptr<Curve> straid2 = shared_ptr<Straight>(new Straight(0.0, 0.0, 1.0, 0.0));

	shared_ptr<Curve> circle1 = shared_ptr<Circle>(new Circle(0, 0, 10.0));

	Intersections intersector;
	vector<Points> solution =  intersector.Intersection(straid1, straid2);

	// shared_ptr<Curve> ptr1 = shared_ptr<Straight>(new Straight());

	std::cin.get();
	return 0;
}