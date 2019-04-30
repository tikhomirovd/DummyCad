//
// Created by dimas on 4/12/19.
//

#include <Circle.h>


Circle::Circle(const Point &theCenter, double theRadius)
{
    myCenter = theCenter;
    myRadius = theRadius;
}

Point Circle::Value(double t)
{
    double aCoordX = myCenter.X() + myRadius * cos(t);
    double aCoordY = myCenter.Y() + myRadius * sin(t);
    return {aCoordX, aCoordY, myCenter.Z()};
}

bool Circle::IsClosed()
{
    return true;
}

Point Circle::Tangent(double t)
{
    return {-myRadius * sin(t), myRadius * cos(t), 0};
}

double Circle::Radius()
{
    return myRadius;
}


const Point &Circle::Center() const
{
    return myCenter;
}