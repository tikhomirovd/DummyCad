//
// Created by dimas on 4/12/19.
//

#ifndef CURVE_POINT_H
#define CURVE_POINT_H

#include <iostream>

using namespace std;


class Point {
private:
    double _x = 0, _y = 0, _z = 0;


public:
    Point();

    explicit Point(double);

    Point(double, double);

    Point(double, double, double);

    void setCoord(double x, double y, double z);

    double x();

    double y();

    double z();

    void getCoord();

    friend Point operator+(Point &a, Point &b) {

        return {a.x() + b.x(), a.y() + b.y(), a.z() + b.z()};
    }

    friend const Point operator*(Point &a, const double &i) {

        return {a.x() * i, a.y() * i, a.z() * i};
    }

    friend const Point operator+(Point &a, const double &i) {

        return {a.x() + i, a.y() + i, a.z() + i};
    }


};


#endif //CURVE_POINT_H
