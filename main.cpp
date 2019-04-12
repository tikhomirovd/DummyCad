#include <iostream>
#include <cmath>
#include "Circle.h"
#include "Line.h"
#include "Point.h"

using namespace std;


void PrintResult(Point tangent, Point value, bool isclosed) {
    cout << "Tangent is \n";
    tangent.getCoord();
    cout << "Value is\n";
    value.getCoord();
    if (isclosed) {
        cout << "Curve is closed\n";
    }
    else {
        cout << "Curve is not closed\n";
    }
}



int main() {
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    double radius = 5;
    double t = 5;
    Circle circle = Circle(O, radius);


    Point c_tangent = circle.tangent(t);
    Point c_value = circle.Value(t);
    bool c_close = circle.isClosed();

    Line line = Line(O, D);

    Point l_tangent = line.tangent(t);
    Point l_value = line.Value(t);
    bool l_close = line.isClosed();

    cout << "\nInformation for circle\n";
    PrintResult(c_tangent, c_value, c_close);

    cout << "\nInformation for line\n";
    PrintResult(l_tangent, l_value, l_close);



    return 0;
}