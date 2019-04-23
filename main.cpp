#include <iostream>
#include <cmath>
#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include <Intersection.h>
#include <Intersection.cpp>


using namespace std;

/**
 * \brief Функция, которая выдаёт всю информацию по кривой.
 * Данная функция выводит на экран вектор касательной к кривой в данной точке,
 * значение координат точки на кривой по заданному параметру,
 * выдаёт информацию о том, является ли кривая замкнутой.
 * @param tangent Вектор касательной
 * @param value Значение координат точки на кривой
 * @param isclosed Булевская функция, которая говорит, является ли кривая замкнутой
 */
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

/**
 * \brief Функция, которая выводит координаты точки
 * @param a Точка или вектор в трёхмерном пространстве
 */
void PrintPoins(Point a) {
    cout << "Cord is ";
    cout << a.x() << ", " << a.y() << ", " << a.z() << ';' << endl;
}


int main() {
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    Point O1 = Point(4, 5, 6);
    Point D1 = Point(2, 6, 9);


    double radius = 5;
    double t = 5;
    shared_ptr<Circle> circle(new Circle(O, radius));
    //shared_ptr<Circle> circle2(new Circle(O1, radius));


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






    return 0;
}