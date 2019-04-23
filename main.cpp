#include <iostream>
#include <cmath>
#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include <Intersection.h>
#include <Intersection.cpp>


using namespace std;


void PrintResult(Point tangent, Point value, bool isclosed) {
    cout << "Tangent is \n";
    tangent.getCoord();
    cout << "Value is\n";
    value.getCoord();
    if (isclosed) {
        cout << "Curve is closed\n";
    } else {
        cout << "Curve is not closed\n";
    }
}


void PrintPoins(Point a) {
    cout << "Cord is ";
    cout << a.x() << ", " << a.y() << ", " << a.z() << ';' << endl;
}

bool isnotNan(Point a) {
    return a.x() != NAN && a.y() != NAN && a.z() != NAN;
}

void InterResult(Intersection test_line, Intersection test_mix, Intersection test_circle) {

    Point test_line_point = test_line.First_Point();
    Point test_mix_point = test_mix.First_Point();
    Point test_circle_point = test_circle.First_Point();


    Point test_mix_point2 = test_mix.Second_Point();
    Point test_circle_point2 = test_circle.Second_Point();

    cout << "\n\nPoints for lines\n";
    if (test_line.current_status())
        PrintPoins(test_line_point);
    else
        cout << "There is no intersection\n";

    cout << "\nPoints for circles\n";
    if (test_circle.current_status()) {
        PrintPoins(test_circle_point);
        PrintPoins(test_circle_point2);
    } else {
        cout << "There is no intersection\n";
    }

    cout << "\nPoints for line and circle \n";
    if (test_mix.current_status()) {
        PrintPoins(test_mix_point);
        PrintPoins(test_mix_point2);
    } else {
        cout << "There is no intersection\n";
    }
}

int main() {
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    Point O1 = Point(4, 5, 6);
    Point D1 = Point(2, 6, 9);


    double radius = 5;
    double t = 5;
    shared_ptr<Circle> circle(new Circle(O, radius));
    shared_ptr<Circle> circle2(new Circle(O1, radius));


    Point c_tangent = circle->tangent(t);
    Point c_value = circle->Value(t);
    bool c_close = circle->isClosed();

    shared_ptr<Line> line(new Line(O, D));
    shared_ptr<Line> line2(new Line(O1, D1));

    Point l_tangent = line->tangent(t);
    Point l_value = line->Value(t);
    bool l_close = line->isClosed();

    cout << "\nInformation for circle\n";
    PrintResult(c_tangent, c_value, c_close);

    cout << "\nInformation for line\n";
    PrintResult(l_tangent, l_value, l_close);


    cout << "\nFirst example\n";
    Intersection test_line = Intersection(line, line);
    Intersection test_mix = Intersection(line, circle);
    Intersection test_circle = Intersection(circle, circle);


    InterResult(test_line, test_mix, test_circle);


    cout << "\nSecond example\n";
    Intersection test_line2 = Intersection(line, line2);
    Intersection test_mix2 = Intersection(line, circle);
    Intersection test_circle2 = Intersection(circle, circle2);


    InterResult(test_line2, test_mix2, test_circle2);


    return 0;
}