#include <iostream>

#include "Curve.h"
#include "Vector.h"
#include "Point.h"
#pragma once

using namespace std;

class Straight : public Curve
{
private:
	double dot1, dot2;

public:
	Straight(double x, double y, double _dot1, double _dot2)
	: Curve(x,y)
	{
		dot1 = _dot1;
		dot2= _dot2;
	};
	bool ClosedCurve() override
	{
		return false;
	};
	double getDot1()
	{
		return dot1;
	};
	double getDot2()
	{
		return dot2;
	};
	Point* PointCalcul(double t)
	{
		double x = point->getX() - dot1*t;
		double y = point->getY() - dot2*t;
		return new Point(x, y);
	};

	/*Point* NormalVector()
	{

	}*/

	Point* TangentCalcul(double t)
	{
		cout << "касательная к прямой - " << endl;
		return new Point(0, 0);
	};
};