#include <iostream>
#include <cmath>
#include "Circle.h"
#include "Line.h"
#include "Point.h"

using namespace std;


int main() {
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    double radius = 5;
    Line l = Line(O, D);
    Circle c = Circle(O, radius);




    return 0;
}