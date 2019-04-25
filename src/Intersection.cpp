//
// Created by dimas on 4/18/19.
//
#include <vector>
#include "Intersection.h"
#include <iostream>
#include <Curve.h>
#include <Line.h>
#include <Circle.h>
#include <Point.h>

using namespace std;

static const double EPS = 1e-9;


Point Second_Point();

Intersection::Intersection(const shared_ptr<Curve> &curve1, const shared_ptr<Curve> &curve2) {
    auto line1 = dynamic_pointer_cast<Line>(curve1);
    if (line1) {
        auto line2 = dynamic_pointer_cast<Line>(curve2);


        if (line2) {
            Intersection::InterPoints(line1, line2);


        } else {
            auto circle1 = dynamic_pointer_cast<Circle>(curve2);
            Intersection::InterPoints(line1, circle1);
        }

    } else {
        auto circle1 = dynamic_pointer_cast<Circle>(curve1);
        if (circle1) {
            auto circle2 = dynamic_pointer_cast<Circle>(curve2);
            if (circle2) {
                Intersection::InterPoints(circle1, circle2);
            } else {
                auto line2 = dynamic_pointer_cast<Circle>(curve2);
                Intersection::InterPoints(line1, circle2);
            }
        }
    }

}


void Intersection::InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Circle> &circle1) {
    double r = circle1->Radius(), a = line1->coef_equation().x(),
            b = line1->coef_equation().y(), c =
            line1->coef_equation().z() + circle1->Center().x() + circle1->Center().y();
    Intersection::InterCircle(r, a, b, c);


}

void Intersection::InterPoints(const shared_ptr<Circle> &circle1, const shared_ptr<Circle> &circle2) {
    double r1 = circle1->Radius(), r2 = circle2->Radius(), a = -2 * circle2->Center().x(),
            b = -2 * circle2->Center().y(), c = pow(circle2->Center().x(), 2) + pow(circle2->Center().y(), 2) +
                                                pow(r1, 2) - pow(r2, 2);

    if (circle1->Center().x() == circle2->Center().x() &&
        circle1->Center().y() == circle2->Center().y()) {
        if (r1 == r2) {
            cout << "It is one circle";
            status = false;
        } else {
            cout << "0 point";
            status = false;
        }
    } else {
        Intersection::InterCircle(r1, a, b, c);
    }


}

void Intersection::InterCircle(double r, double a, double b, double c) {
    double x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    cout << "\nkek\n";
    cout << r << " " << a << " " << b << " " << c << endl;
    if (c * c > r * r * (a * a + b * b) + EPS) {
        cout << "0 point";
        status = false;
    } else if (abs(c * c - r * r * (a * a + b * b)) < EPS) {
        puts("1 point");
        status = true;
        cout << x0 << ' ' << y0 << '\n';
        inter.emplace_back(x0, y0, 0);
        status = true;
    } else {
        double d = r * r - c * c / (a * a + b * b);
        double mult = sqrt(d / (a * a + b * b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        puts("2 points");
        cout << ax << ", " << ay << ";\n" << bx << ", " << by << ";\n";
        inter.emplace_back(ax, ay, 0);
        inter.emplace_back(bx, by, 0);
        status = true;
    }
}

void Intersection::InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2) {


    double zn = Intersection::det(line1->coef_equation().x(), line1->coef_equation().y(),
                                  line2->coef_equation().x(), line2->coef_equation().y());

    if (Intersection::isParallel(line1, line2) && !Intersection::isEquivalent(line1, line2)) {
        status = false;
    } else if (Intersection::isEquivalent(line1, line2)) {
        status = false;
    } else if (abs(zn) >= EPS) {
        double resx, resy;
        resx = -Intersection::det(line1->coef_equation().z(), line1->coef_equation().y(),
                                  line2->coef_equation().z(), line2->coef_equation().y()) / zn;
        resy = -Intersection::det(line1->coef_equation().x(), line1->coef_equation().z(),
                                  line2->coef_equation().x(), line2->coef_equation().z()) / zn;


        inter.emplace_back(resx, resy, 0);
        status = true;
    }
}


bool Intersection::isParallel(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2) {

    if (abs(det(line1->coef_equation().x(), line1->coef_equation().y(),
                line2->coef_equation().x(), line2->coef_equation().y())) < EPS) {
        cout << "Lines are Parallel\n";
        return true;
    }
    return false;
}

bool Intersection::isEquivalent(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2) {
    if (abs(det(line1->coef_equation().x(), line1->coef_equation().y(),
                line2->coef_equation().x(), line2->coef_equation().y())) < EPS
        && abs(det(line1->coef_equation().x(), line2->coef_equation().z(),
                   line2->coef_equation().x(), line2->coef_equation().z())) < EPS
        && abs(det(line1->coef_equation().y(), line1->coef_equation().z(),
                   line2->coef_equation().y(), line2->coef_equation().z())) < EPS) {
        cout << "Lines are equivalent\n";
        return true;
    }
    return false;
}


double Intersection::det(double a, double b, double c, double d) {
    return a * d - b * c;
}

Point Intersection::First_Point() {
    if (!inter.empty())
        return inter[0];
    return {NAN, NAN, NAN};
}

Point Intersection::Second_Point() {

    return inter[1];

}

bool Intersection::current_status() {
    return status;
}
