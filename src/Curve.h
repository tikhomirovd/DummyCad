#pragma once

#include "Point.h"

class Curve 
{
public :

	Point* point;

	Curve(double x, double y)
	{
		point = new Point(x, y);
	}

	Point* getCurvePoint()
	{
		return point;
	}

public:
	virtual Point* PointCalcul(double t) = 0; // координата в зависимости от параметра 
	virtual Point* TangentCalcul(double t) = 0; // касательная к кривой
	virtual bool ClosedCurve() = 0; // является ли кривая замкнутой
};