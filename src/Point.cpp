//
// Created by dimas on 4/12/19.
//

#include "Point.h"

Point::Point()
{
    SetCoord(0, 0, 0);
}


Point::Point(double x)
{
    SetCoord(x, 0, 0);
}

Point::Point(double x, double y)
{
    SetCoord(x, y, 0);
}

Point::Point(double x, double y, double z)
{
    SetCoord(x, y, z);
}

double Point::X() const
{
    return theCoordX;
}

double Point::Y() const
{
    return theCoordY;
}

double Point::Z() const
{
    return theCoordZ;
}

void Point::SetCoord(double x, double y, double z)
{
    theCoordX = x;
    theCoordY = y;
    theCoordZ = z;
    
}


