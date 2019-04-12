//
// Created by dimas on 4/12/19.
//

#ifndef CURVE_CIRCLE_H
#define CURVE_CIRCLE_H


#include "Point.h"
#include "Curve.h"
#include <cmath>

class Curve_EXPORT Circle : Curve {
private:
    Point center;
    double radius{};


public:
    Circle() : Curve() {}

    Circle(Point ccenter, double r);

    Point Value(double t) override;

    bool isClosed() override;

    Point tangent(double t) override;

};


#endif //CURVE_CIRCLE_H
