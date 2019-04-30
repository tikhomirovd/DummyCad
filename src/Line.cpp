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
    Point aNewDirect = direct * t;
    return aNewDirect + center;
}

bool Line::IsClosed()
{
    return false;
}

Point Line::Tangent(double)
{
    return direct;
}

Point Line::CoefEquation()
{
    return {direct.Y(), -direct.X(), direct.X() * center.Y() - direct.Y() * center.X()};
}


