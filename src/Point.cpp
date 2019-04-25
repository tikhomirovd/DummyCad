//
// Created by dimas on 4/12/19.
//

#include "Point.h"

Point::Point() {
    setCoord(0, 0, 0);
}


Point::Point(double x) {
    setCoord(x, 0, 0);
}

Point::Point(double x, double y) {
    setCoord(x, y, 0);
}

Point::Point(double x, double y, double z) {
    setCoord(x, y, z);
}

double Point::x() const {
    return _x;
}

double Point::y() const {
    return _y;
}

double Point::z() const {
    return _z;
}

void Point::setCoord(double x, double y, double z) {
    _x = x;
    _y = y;
    _z = z;

}

void Point::getCoord() {
    cout << "x = " << _x << "; y = " << _y << "; z = " << _z << endl;
}

