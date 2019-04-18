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
	Straight(double x, double y, double _dot1, double _dot2) : Curve(x,y)
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
	Points* PointCalcul(double t)
	{
		dot1 = point->getX()*t - point->getX();
		dot2 = point->getY()*t - point->getY();
		return new Points(dot1, dot2);
	};

	Points* TangentCalcul(double t)
	{
		cout << "касательная к прямой - " << endl;
		return new Points(0, 0);
	};
};