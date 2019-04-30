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

//enumerate




Intersection::Intersection(const shared_ptr<Curve> &curve1, const shared_ptr<Curve> &curve2)
{
    auto line1 = dynamic_pointer_cast<Line>(curve1);
    if ( line1 )
    {
        auto line2 = dynamic_pointer_cast<Line>(curve2);
        
        
        if ( line2 )
        {
            Intersection::InterPoints(line1, line2);
            
            
        } else
        {
            auto circle1 = dynamic_pointer_cast<Circle>(curve2);
            if ( circle1 )
            {
                Intersection::InterPoints(line1, circle1);
            }
        }
        
    } else
    {
        auto circle1 = dynamic_pointer_cast<Circle>(curve1);
        if ( circle1 )
        {
            auto circle2 = dynamic_pointer_cast<Circle>(curve2);
            if ( circle2 )
            {
                Intersection::InterPoints(circle1, circle2);
            } else
            {
                auto line2 = dynamic_pointer_cast<Circle>(curve2);
                if ( line2 )
                {
                    Intersection::InterPoints(line1, circle2);
                }
            }
        }
    }
    
}


void Intersection::InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Circle> &circle1)
{
    double r = circle1->Radius(), a = line1->Coef_equation().X(),
            b = line1->Coef_equation().Y(), c =
            line1->Coef_equation().Z() + circle1->Center().X() + circle1->Center().Y();
    Intersection::InterCircleLine(r, a, b, c);
    
    
}

void Intersection::InterPoints(const shared_ptr<Circle> &circle1, const shared_ptr<Circle> &circle2)
{
    double r1 = circle1->Radius(), r2 = circle2->Radius();
    
    double d = sqrt(pow(circle1->Center().X() - circle2->Center().X(), 2)
                    + pow(circle1->Center().Y() - circle2->Center().Y(), 2));
    
    
    if ( d < EPS && fabs(r1 - r2) < EPS )
    {
        status = EQUAL;
    } else if ( d > r1 + r2 or d < fabs(r1 - r2))
    {
        status = NOT_INTERSECTED;
    } else
    {
        double a = (pow(r1, 2) - pow(r2, 2) + pow(d, 2) / (2 * d));
        double h = sqrt(pow(r1, 2) - pow(a, 2));
        double x1 = circle1->Center().X(), x2 = circle2->Center().X();
        double y1 = circle1->Center().Y(), y2 = circle2->Center().Y();
        Point P3 = circle1->Center() + (circle2->Center() - circle1->Center()) * (a / d);
        double ans_x1 = P3.X() + h / d * (y2 - y1);
        double ans_y1 = P3.Y() - h / d * (x2 - x1);
        double ans_x2 = P3.X() - h / d * (y2 - y1);
        double ans_y2 = P3.Y() + h / d * (x2 - x1);
        inter.emplace_back(ans_x1, ans_y1, 0);
        if ( ans_x1 != ans_x2 && ans_y1 != ans_y2 )
        {
            inter.emplace_back(ans_x2, ans_y2, 0);
        }
        status = DONE;
    }
    
    
}

void Intersection::InterCircleLine(double r, double a, double b, double c)
{
    double x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    if ( c * c > r * r * (a * a + b * b) + EPS )
    {
        status = NOT_INTERSECTED;
    } else if ( fabs(c * c - r * r * (a * a + b * b)) < EPS )
    {
        status = DONE;
        inter.emplace_back(x0, y0, 0);
    } else
    {
        double d = r * r - c * c / (a * a + b * b);
        double mult = sqrt(d / (a * a + b * b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        inter.emplace_back(ax, ay, 0);
        inter.emplace_back(bx, by, 0);
        status = DONE;
    }
}

void Intersection::InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2)
{
    
    
    double zn = det(line1->Coef_equation().X(), line1->Coef_equation().Y(),
                    line2->Coef_equation().X(), line2->Coef_equation().Y());
    
    if ( Intersection::IsEquivalent(line1, line2))
    {
        status = EQUAL;
    } else if ( Intersection::IsParallel(line1, line2))
    {
        status = NOT_INTERSECTED;
    } else
    {
        double resx, resy;
        resx = -det(line1->Coef_equation().Z(), line1->Coef_equation().Y(),
                    line2->Coef_equation().Z(), line2->Coef_equation().Y()) / zn;
        resy = -det(line1->Coef_equation().X(), line1->Coef_equation().Z(),
                    line2->Coef_equation().X(), line2->Coef_equation().Z()) / zn;
        
        
        inter.emplace_back(resx, resy, 0);
        status = DONE;
    }
}


bool Intersection::IsParallel(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2)
{
    
    return fabs(det(line1->Coef_equation().X(), line1->Coef_equation().Y(),
                    line2->Coef_equation().X(), line2->Coef_equation().Y())) < EPS;
}

bool Intersection::IsEquivalent(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2)
{
    return fabs(det(line1->Coef_equation().X(), line1->Coef_equation().Y(),
                    line2->Coef_equation().X(), line2->Coef_equation().Y())) < EPS
           && fabs(det(line1->Coef_equation().X(), line2->Coef_equation().Z(),
                       line2->Coef_equation().X(), line2->Coef_equation().Z())) < EPS
           && fabs(det(line1->Coef_equation().Y(), line1->Coef_equation().Z(),
                       line2->Coef_equation().Y(), line2->Coef_equation().Z())) < EPS;
}


static double det(double a, double b, double c, double d)
{
    return a * d - b * c;
}

const Point &Intersection::First_Point()
{
    if ( NumberInter())
        return inter[0];
    return {NAN, NAN, NAN};
}

const Point &Intersection::Second_Point()
{
    if ( NumberInter() >= 2 )
    {
        return inter[1];
    }
    return {NAN, NAN, NAN};
    
}

Intersection::InterStatus Intersection::Current_status()
{
    return status;
}

int Intersection::NumberInter()
{
    return inter.size();
}

