#include <iostream>
#include <cmath>
#include <Circle.h>
#include <Line.h>
#include <Point.h>
#include <Intersection.h>
#include <Intersection.cpp>


using namespace std;



int main() {
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    Point O1 = Point(4, 5, 6);
    Point D1 = Point(2, 6, 9);


    double radius = 5;
    double t = 5;
    shared_ptr<Circle> circle(new Circle(O, radius));
    //shared_ptr<Circle> circle2(new Circle(O1, radius));


    Point c_tangent = circle->Tangent(t);
    Point c_value = circle->Value(t);
    bool c_close = circle->IsClosed();

    shared_ptr<Line> line(new Line(O, D));
    shared_ptr<Line> line2(new Line(O1, D1));

    Point l_tangent = line->Tangent(t);
    Point l_value = line->Value(t);
    bool l_close = line->IsClosed();






    return 0;
}