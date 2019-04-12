//
// Created by dimas on 4/12/19.
//

#ifndef CURVE_CURVE_H
#define CURVE_CURVE_H


#include "Point.h"

class Curve {


public:
    Curve() = default;

    virtual Point Value(double t) = 0;

    virtual bool isClosed() = 0;

    virtual Point tangent(double t) = 0;


};


#endif //CURVE_CURVE_H