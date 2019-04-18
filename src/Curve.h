#include <iostream>
#include "Point.h"
#pragma once

class Curve 
{
public :

	Points* point;

	Curve(double x, double y)
	{
		point = new Points(x, y);
	}

	Points* getCurvePoint()
	{
		return point;
	}

public:
	virtual Points* PointCalcul(double t) = 0; // координата в зависимости от параметра 
	virtual Points* TangentCalcul(double t) = 0; // касательная к кривой
	virtual bool ClosedCurve() = 0; // является ли кривая замкнутой
};