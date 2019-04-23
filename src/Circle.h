//
// Created by dimas on 4/12/19.
//

#ifndef CURVE_CIRCLE_H
#define CURVE_CIRCLE_H


#include "Point.h"
#include "Curve.h"
#include <cmath>

class Curve_EXPORT Circle : public Curve {
private:
    Point center;
    double radius;



public:
    Circle() : Curve() {}

    Circle(Point ccenter, double r);

    Point Value(double t) override;

    bool isClosed() override;
    double Radius();

    Point tangent(double t) override;

    Point Center();


};


#endif //CURVE_CIRCLE_H
