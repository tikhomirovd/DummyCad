//
// Created by dimas on 4/18/19.
//

#include "Intersection.h"
#include <iostream>
#include <Curve.h>
#include <Line.h>
#include <Circle.h>
#include <Point.h>

using namespace std;

const double EPS = 1e-9;


Intersection::Intersection(const shared_ptr<Curve> &curve1, const shared_ptr<Curve> &curve2) {
    auto line1 = dynamic_pointer_cast<Line>(curve1);
    if (line1) {
        auto line2 = dynamic_pointer_cast<Line>(curve2);


        if (line2) {
            Intersection::InterPoints(line1, line2);


        } else {
            auto circle1 = dynamic_pointer_cast<Circle>(curve2);
            // Intersection::isInter(line1, circle1);
        }

    } else {
        auto circle1 = dynamic_pointer_cast<Circle>(curve1);
        auto circle2 = dynamic_pointer_cast<Circle>(curve2);
        if (circle2) {
            Intersection::InterPoints(circle1, circle2);
        } else {
            auto line2 = dynamic_pointer_cast<Circle>(curve2);
            //Intersection::isInter(line1, circle2);
        }
    }

}


void Intersection::InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Circle> &circle1) {
    double r = circle1->Radius(), a = line1->coef_equation().x(),
            b = line1->coef_equation().y() - circle1->Center().y(), c = line1->coef_equation().z();
    Intersection::InterCircle(r, a, b, c, circle1->Center().x(), circle1->Center().y());


}

void Intersection::InterPoints(const shared_ptr<Circle> &circle1, const shared_ptr<Circle> &circle2) {
    double r1 = circle1->Radius(), r2 = circle2->Radius(), a = -2 * circle1->Center().x(),
            b = -2 * circle1->Center().y(), c = pow(circle1->Center().x(), 2) + pow(-2 * circle1->Center().y(), 2) +
                                                pow(circle1->Radius(), 2) - pow(circle2->Radius(), 2);

    if (circle1->Center().x() == circle2->Center().x() &&
        circle1->Center().y() == circle2->Center().y()) {
        if (circle1->Radius() == circle2->Radius()) {
            cout << "It is one circle";
        } else {
            inter = {NAN, NAN, NAN};
        }
    } else {
        Intersection::InterCircle(r1, a, b, c, circle2->Center().x(), circle2->Center().y());
    }


}

void Intersection::InterCircle(double r, double a, double b, double c, double x, double y) {
    double x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    if (c * c > r * r * (a * a + b * b) + EPS)
        inter = {NAN, NAN, NAN};
    else if (abs(c * c - r * r * (a * a + b * b)) < EPS) {
        puts("1 point");
        cout << x0 << ' ' << y0 << '\n';
        inter = {x0, y0, 0};
    } else {
        double d = r * r - c * c / (a * a + b * b);
        double mult = sqrt(d / (a * a + b * b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        puts("2 points");
        cout << ax + x << ' ' << ay + y << '\n' << bx + x << ' ' << by + y << '\n';
    }
}

void Intersection::InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2) {


    double zn = Intersection::det(line1->coef_equation().x(), line1->coef_equation().y(),
                                  line2->coef_equation().x(), line2->coef_equation().y());

    if (abs(zn) >= EPS) {
        Intersection::InterPoints(line1, line2);
        double resx, resy;
        resx = -Intersection::det(line1->coef_equation().z(), line1->coef_equation().y(),
                                  line2->coef_equation().z(), line2->coef_equation().y()) / zn;
        resy = -Intersection::det(line1->coef_equation().x(), line1->coef_equation().z(),
                                  line2->coef_equation().x(), line2->coef_equation().z()) / zn;


        inter = {resx, resy, 0};
    } else inter = {NAN, NAN, NAN};
}


bool Intersection::isParallel(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2) {
    return abs(det(line1->coef_equation().x(), line1->coef_equation().y(),
                   line2->coef_equation().x(), line2->coef_equation().y())) < EPS;
}

bool Intersection::isEquivalent(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2) {
    return abs(det(line1->coef_equation().x(), line1->coef_equation().y(),
                   line2->coef_equation().x(), line2->coef_equation().y())) < EPS
           && abs(det(line1->coef_equation().x(), line2->coef_equation().z(),
                      line2->coef_equation().x(), line2->coef_equation().z())) < EPS
           && abs(det(line1->coef_equation().y(), line1->coef_equation().z(),
                      line2->coef_equation().y(), line2->coef_equation().z())) < EPS;
}


Point Intersection::Points() {
    return inter;
}


double Intersection::det(double a, double b, double c, double d) {
    return a * d - b * c;
}
