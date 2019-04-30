//
// Created by dimas on 4/12/19.
//

#include "Circle.h"


Circle::Circle(const Point &theCenter, double theRadius)
{
    center = theCenter;
    radius = theRadius;
}

Point Circle::Value(double t)
{
    double coordX = center.X() + radius * cos(t);
    double coordY = center.Y() + radius * sin(t);
    return {coordX, coordY, center.Z()};
}

bool Circle::IsClosed()
{
    return true;
}

Point Circle::Tangent(double t)
{
    return {-radius * sin(t), radius * cos(t), 0};
}

double Circle::Radius()
{
    return radius;
};


const Point &Circle::Center() const
{
    return center;
}