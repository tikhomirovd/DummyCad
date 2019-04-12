//
// Created by dimas on 4/12/19.
//

#include "Line.h"


Line::Line(Point ccenter, Point ddirect) {
    center = ccenter;
    direct = ddirect;
}

Point Line::Value(double t) {
    return direct * t + center ;
}

bool Line::isClosed() {
    return false;
}

Point Line::tangent(double t) {
    return direct;
}

