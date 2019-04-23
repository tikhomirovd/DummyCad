//
// Created by dimas on 4/12/19.
//

#include "Circle.h"

Circle::Circle(Point ccenter, double r) {
    center = ccenter;
    radius = r;
}

Point Circle::Value(double t) {
    double cordX = center.x() + radius * sin(t);
    double cordY = center.y() + radius * cos(t);
    return {cordX, cordY, center.z()};
}

bool Circle::isClosed() {
    return true;
}

Point Circle::tangent(double t) {
    return {radius * cos(t), -radius * sin(t), 0};
}

double Circle::Radius() {
    return radius;
}

Point Circle::Center(){
    return center;
}