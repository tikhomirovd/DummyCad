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

static const auto EPS = 1e-9;

//enumerate


static double det(double, double, double, double);

Intersection::Intersection(const shared_ptr<Curve> &curve1, const shared_ptr<Curve> &curve2)
{
    auto aLine1 = dynamic_pointer_cast<Line>(curve1);
    if ( aLine1 )
    {
        auto aLine2 = dynamic_pointer_cast<Line>(curve2);
        
        
        if ( aLine2 )
        {
            Intersection::InterPoints(aLine1, aLine2);
            
            
        } else
        {
            auto aCircle1 = dynamic_pointer_cast<Circle>(curve2);
            if ( aCircle1 )
            {
                Intersection::InterPoints(aLine1, aCircle1);
            }
        }
        
    } else
    {
        auto aCircle1 = dynamic_pointer_cast<Circle>(curve1);
        if ( aCircle1 )
        {
            auto aCircle2 = dynamic_pointer_cast<Circle>(curve2);
            if ( aCircle2 )
            {
                Intersection::InterPoints(aCircle1, aCircle2);
            } else
            {
                auto aLine2 = dynamic_pointer_cast<Circle>(curve2);
                if ( aLine2 )
                {
                    Intersection::InterPoints(aLine1, aCircle2);
                } else
                {
                    theStatus = NOT_SUPPORTED_CURVE;
                }
            }
        } else
        {
            theStatus = NOT_SUPPORTED_CURVE;
        }
    }
    
}


void Intersection::InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Circle> &circle1)
{
    double aRadius = circle1->Radius(), aCoefA = line1->CoefEquation().X(),
            aCoefB = line1->CoefEquation().Y(),
            aCoefC = line1->CoefEquation().Z() + circle1->Center().X() + circle1->Center().Y();
    Intersection::InterCircleLine(aRadius, aCoefA, aCoefB, aCoefC);
    
    
}

void Intersection::InterPoints(const shared_ptr<Circle> &circle1, const shared_ptr<Circle> &circle2)
{
    double aRadius1 = circle1->Radius(), aRadius2 = circle2->Radius();
    
    double aDistance = sqrt(pow(circle1->Center().X() - circle2->Center().X(), 2) +
                            pow(circle1->Center().Y() - circle2->Center().Y(), 2));
    
    
    if ( aDistance < EPS && fabs(aRadius1 - aRadius2) < EPS )
    {
        theStatus = EQUAL;
    } else if ( aDistance > aRadius1 + aRadius2 or aDistance < fabs(aRadius1 - aRadius2))
    {
        theStatus = NOT_INTERSECTED;
    } else
    {
        double aCut = ((pow(aRadius1, 2) - pow(aRadius2, 2) + pow(aDistance, 2)) / (2 * aDistance));
        double aHeight = sqrt(pow(aRadius1, 2) - pow(aCut, 2));
        double aX1 = circle1->Center().X(), aX2 = circle2->Center().X();
        double aY1 = circle1->Center().Y(), aY2 = circle2->Center().Y();
        Point aP3 = circle1->Center() + (circle2->Center() - circle1->Center()) * (aCut / aDistance);
        double aAnsX1 = aP3.X() + aHeight / aDistance * (aY2 - aY1);
        double aAnsY1 = aP3.Y() - aHeight / aDistance * (aX2 - aX1);
        double aAnsX2 = aP3.X() - aHeight / aDistance * (aY2 - aY1);
        double aAnsY2 = aP3.Y() + aHeight / aDistance * (aX2 - aX1);
        theInter.emplace_back(aAnsX1, aAnsY1, 0);
        if ( aAnsX1 != aAnsX2 && aAnsY1 != aAnsY2 )
        {
            theInter.emplace_back(aAnsX2, aAnsY2, 0);
        }
        theStatus = DONE;
    }
    
    
}

void Intersection::InterCircleLine(double r, double a, double b, double c)
{
    double aX0 = -a * c / (a * a + b * b), aY0 = -b * c / (a * a + b * b);
    if ( c * c > r * r * (a * a + b * b) + EPS )
    {
        theStatus = NOT_INTERSECTED;
    } else if ( fabs(c * c - r * r * (a * a + b * b)) < EPS )
    {
        theStatus = DONE;
        theInter.emplace_back(aX0, aY0, 0);
    } else
    {
        double aDistance = r * r - c * c / (a * a + b * b);
        double aMult = sqrt(aDistance / (a * a + b * b));
        double ax, ay, bx, by;
        ax = aX0 + b * aMult;
        bx = aX0 - b * aMult;
        ay = aY0 - a * aMult;
        by = aY0 + a * aMult;
        theInter.emplace_back(ax, ay, 0);
        theInter.emplace_back(bx, by, 0);
        theStatus = DONE;
    }
}

void Intersection::InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2)
{
    
    
    double aZn = det(line1->CoefEquation().X(), line1->CoefEquation().Y(),
                     line2->CoefEquation().X(), line2->CoefEquation().Y());
    
    if ( Intersection::IsEquivalent(line1, line2))
    {
        theStatus = EQUAL;
    } else if ( Intersection::IsParallel(line1, line2))
    {
        theStatus = NOT_INTERSECTED;
    } else
    {
        double aResx, aResy;
        aResx = -det(line1->CoefEquation().Z(), line1->CoefEquation().Y(),
                     line2->CoefEquation().Z(), line2->CoefEquation().Y()) / aZn;
        aResy = -det(line1->CoefEquation().X(), line1->CoefEquation().Z(),
                     line2->CoefEquation().X(), line2->CoefEquation().Z()) / aZn;
        
        
        theInter.emplace_back(aResx, aResy, 0);
        theStatus = DONE;
    }
}


bool Intersection::IsParallel(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2)
{
    
    return fabs(det(line1->CoefEquation().X(), line1->CoefEquation().Y(),
                    line2->CoefEquation().X(), line2->CoefEquation().Y())) < EPS;
}

bool Intersection::IsEquivalent(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2)
{
    return fabs(det(line1->CoefEquation().X(), line1->CoefEquation().Y(),
                    line2->CoefEquation().X(), line2->CoefEquation().Y())) < EPS
           && fabs(det(line1->CoefEquation().X(), line2->CoefEquation().Z(),
                       line2->CoefEquation().X(), line2->CoefEquation().Z())) < EPS
           && fabs(det(line1->CoefEquation().Y(), line1->CoefEquation().Z(),
                       line2->CoefEquation().Y(), line2->CoefEquation().Z())) < EPS;
}


static double det(double a, double b, double c, double d)
{
    return a * d - b * c;
}

const Point &Intersection::FirstPoint()
{
    if ( NumberInter())
        return theInter[0];
    return {NAN, NAN, NAN};
}

const Point &Intersection::SecondPoint()
{
    if ( NumberInter() >= 2 )
    {
        return theInter[1];
    }
    return {NAN, NAN, NAN};
    
}

Intersection::InterStatus Intersection::CurrentStatus()
{
    return theStatus;
}

int Intersection::NumberInter()
{
    return theInter.size();
}

