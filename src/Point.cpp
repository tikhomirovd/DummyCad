//
// Created by dimas on 4/12/19.
//

#include <Point.h>

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
    return myCoordX;
}

double Point::Y() const
{
    return myCoordY;
}

double Point::Z() const
{
    return myCoordZ;
}

void Point::SetCoord(double x, double y, double z)
{
    myCoordX = x;
    myCoordY = y;
    myCoordZ = z;
    
}


