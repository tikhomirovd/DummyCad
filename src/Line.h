//
// Created by dimas on 4/12/19.
//

#ifndef CURVE_LINE_H
#define CURVE_LINE_H


#include "Curve.h"
#include "Point.h"

class Curve_EXPORT Line : public Curve {
private:
    Point center, direct;


public:
    Line() : Curve() {}


    Line(Point, Point);

    Point Value(double) override;

    bool isClosed() override;

    Point tangent(double t) override;


    Point coef_equation();
};


#endif //CURVE_LINE_H