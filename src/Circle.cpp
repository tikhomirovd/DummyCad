#include <iostream>
#include <math.h>

#include "Curve.h"
#include "Vector.h"
#include "Point.h"
#pragma once

class Circle : public Curve
{
	double Radius;
public:
	Circle(int x, int y, double radius) : Curve(x,y)
	{
		Radius = radius;
	}

	double getRadius()
	{
		return Radius;
	}

	Points* getCurvePoint()
	{
		return point;
	}

	bool ClosedCurve() override
	{
		return true;
	};

	Points* TangentCalcul(double t)
	{
		double x = Radius * (-sin(t));
		double y = Radius * cos(t);
		return new Points(x, y);
	};

	Points* PointCalcul(double t) 
	{
		return new Points(Radius*cos(t), Radius*sin(t));
	};
};
