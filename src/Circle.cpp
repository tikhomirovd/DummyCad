//
// Created by dimas on 4/12/19.
//

#include "Circle.h"


Circle::Circle(const Point &ccenter, double r) {
    center = ccenter;
    radius = r;
}

Point Circle::Value(double t) {
    double cordX = center.x() + radius * cos(t);
    double cordY = center.y() + radius * sin(t);
    return {cordX, cordY, center.z()};
}

bool Circle::isClosed() {
    return true;
}

Point Circle::tangent(double t) {
    return {-radius * sin(t), radius * cos(t), 0};
}

double Circle::Radius() {
    return radius;
};


const Point &Circle::Center() const {
    return center;
}