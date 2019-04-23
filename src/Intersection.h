//
// Created by dimas on 4/18/19.
//

#ifndef CURVE_INTERSECTION_H
#define CURVE_INTERSECTION_H

#include <Curve.h>
#include <Line.h>
#include <iostream>
#include <Circle.h>
#include <memory>
#include <Point.h>
#include <vector>

using namespace std;


class Curve_EXPORT Intersection {
private:
    vector <Point> inter = {};
    bool status = false;


public:
    Intersection(const shared_ptr<Curve> &, const shared_ptr<Curve> &);


    double det(double, double, double, double);

   // Point InterPoints();




    void InterPoints(const shared_ptr<Line>& line1, const shared_ptr<Line>& line2);
    void InterPoints(const shared_ptr<Circle>& circle1, const shared_ptr<Circle>& circle2);
    void InterPoints(const shared_ptr<Line>& line1, const shared_ptr<Circle>& circle2);


    bool isParallel(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2);

    bool isEquivalent(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2);



    Point First_Point();
    Point Second_Point();

    bool current_status();

    void InterCircle(double r, double a, double b, double c);
};


#endif //CURVE_INTERSECTION_H
