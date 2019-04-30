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
    return coord_x;
}

double Point::Y() const
{
    return coord_y;
}

double Point::Z() const
{
    return coord_z;
}

void Point::SetCoord(double x, double y, double z)
{
    x = x;
    y = y;
    z = z;
    
}


