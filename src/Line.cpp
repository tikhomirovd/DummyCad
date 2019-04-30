//
// Created by dimas on 4/12/19.
//

#include "Line.h"


Line::Line(const Point &ccenter, const Point &ddirect)
{
    myCenter = ccenter;
    myDirect = ddirect;
}

Point Line::Value(double t)
{
    Point aNewDirect = myDirect * t;
    return aNewDirect + myCenter;
}

bool Line::IsClosed()
{
    return false;
}

Point Line::Tangent(double)
{
    return myDirect;
}

Point Line::CoefEquation()
{
    return {myDirect.Y(), -myDirect.X(), myDirect.X() * myCenter.Y() - myDirect.Y() * myCenter.X()};
}


