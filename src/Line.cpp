//
// Created by dimas on 4/12/19.
//

#include "Line.h"


Line::Line(const Point &ccenter, const Point &ddirect) {
    center = ccenter;
    direct = ddirect;
}

Point Line::Value(double t) {
    Point new_direct = direct * t;
    return new_direct + center ;
}

bool Line::isClosed() {
    return false;
}

Point Line::tangent(double t)  {
    return direct;
}

Point Line::coef_equation() {
    return {direct.y(), -direct.x(), direct.x() * center.y() - direct.y() * center.x()};
}


