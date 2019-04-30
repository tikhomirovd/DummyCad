//
// Created by dimas on 4/12/19.
//

#include "Line.h"


Line::Line(const Point &ccenter, const Point &ddirect)
{
    center = ccenter;
    direct = ddirect;
}

Point Line::Value(double t)
{
    Point new_direct = direct * t;
    return new_direct + center;
}

bool Line::IsClosed()
{
    return false;
}

Point Line::Tangent(double t)
{
    return direct;
}

Point Line::Coef_equation()
{
    return {direct.Y(), -direct.X(), direct.X() * center.Y() - direct.Y() * center.X()};
}


