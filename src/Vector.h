#include <iostream>
#pragma once

class Vector
{
private:
	double dot1;
	double dot2;
public :
	Vector(double a, double b)
	{
		dot1 = a;
		dot2 = b;
	}
	// получение координаты x вектора
	double getDot1()
	{
		return dot1;
	}
	// получение координаты y вектора
	double getDot2()
	{
		return dot2;
	}
};
