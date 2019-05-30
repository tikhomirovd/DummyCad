//
// Created by dimas on 4/12/19.
//

#include <Line.h>


Line::Line(const Point &theCenter, const Point &theDirect)
{
    myCenter = theCenter;
    myDirect = theDirect;
    myDirect.Normalize();
}

Point Line::Value(double t) const
{
    Point aNewDirect = myDirect * t;
    return aNewDirect + myCenter;
}

bool Line::IsClosed() const
{
    return false;
}

Point Line::Tangent(double) const
{
    return myDirect;
}

Point Line::CoefEquation()
{
    return {myDirect.Y(), -myDirect.X(), myDirect.X() * myCenter.Y() - myDirect.Y() * myCenter.X()};
}

Point Line::Center()
{
    return myCenter;
}

Point Line::Direct()
{
    return myDirect;
}


