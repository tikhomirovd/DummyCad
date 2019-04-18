#include <iostream>
#pragma once

class Points 
{
public:

	double x;
	double y;

public:

	Points() {};

	Points(double _x, double _y)
	{
		x = _x;
		y = _y;
	}

	// возврат координаты "x" у точки
	double getX()
	{
		return x;
	}

	// возврат координаты "y" у точки
	double getY()
	{
		return y;
	}
};
