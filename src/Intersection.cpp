//
// Created by dimas on 4/18/19.
//
#include <vector>
#include <Intersection.h>
#include <iostream>
#include <Curve.h>
#include <Line.h>
#include <Circle.h>
#include <Point.h>

using namespace std;

static const auto EPS = 1e-9;

//enumerate

/**
* \brief Вычисляет определитель матрицы 2х2
* \return Определитель
*/

static double det(double, double, double, double);

/**
* \brief Проверяет, являются ли прямые параллельными
* \param line1 Первая линия
* \param line2 Вторая линия
 *
*/
static bool IsParallel(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2);

/**
* \brief Проверяет, совпадают ли прямые
* \param line1 Первая линия
* \param line2 Вторая линия
 *
*/
static bool IsEquivalent(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2);

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
                auto aLine2 = dynamic_pointer_cast<Line>(curve2);
                if ( aLine2 )
                {
                    Intersection::InterPoints(aLine2, aCircle2);
                } else
                {
                    myStatus = NOT_SUPPORTED_CURVE;
                }
            }
        } else
        {
            myStatus = NOT_SUPPORTED_CURVE;
        }
    }
    
}


void Intersection::InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Circle> &circle1)
{
 
    
    double k = -line1->CoefEquation().X() / line1->CoefEquation().Y();
    double d = -line1->CoefEquation().Z() / line1->CoefEquation().Y();
    
    double aDelta =
            pow(circle1->Radius(), 2) * (1 + pow(k, 2)) - pow(circle1->Center().Y() - k * circle1->Center().X() - d, 2);
    
    
    if ( aDelta < -EPS )
    {
        myStatus = NOT_INTERSECTED;
    }
    else
    {
        
        myStatus = DONE;
        double A = circle1->Center().X();
        double B = circle1->Center().Y();
        
        double aSqrK = 1 + pow(k, 2);
        
        if (aDelta > EPS)
        {
    
            double aX0 = (A + B * k - d * k + sqrt(aDelta)) / aSqrK;
            double aX1 = (A + B * k - d * k - sqrt(aDelta)) / aSqrK;
            double aY0 = (d + A * k + B * pow(k, 2) + k * sqrt(aDelta)) / aSqrK;
            double aY1 = (d + A * k + B * pow(k, 2) - k * sqrt(aDelta)) / aSqrK;
    
            myInter.emplace_back(aX0, aY0, 0);
            myInter.emplace_back(aX1, aY1, 0);
    
        } else {
            double aX0 = (A + B * k - d * k) / aSqrK;
            double aY0 = (d + A * k + B * pow(k, 2)) / aSqrK;
            myInter.emplace_back(aX0, aY0, 0);
            
        }
        
      
    }
    
}

void Intersection::InterPoints(const shared_ptr<Circle> &circle1, const shared_ptr<Circle> &circle2)
{
    double aRadius1 = circle1->Radius(), aRadius2 = circle2->Radius();
    
    double aDistance = sqrt(pow(circle1->Center().X() - circle2->Center().X(), 2) +
                            pow(circle1->Center().Y() - circle2->Center().Y(), 2));
    
    
    if ( aDistance < EPS && fabs(aRadius1 - aRadius2) < EPS )
    {
        myStatus = EQUAL;
    } else if ( aDistance > aRadius1 + aRadius2 || aDistance < fabs(aRadius1 - aRadius2))
    {
        myStatus = NOT_INTERSECTED;
    } else
    {
        static const double TOL = 1.e-7;
        double aCut = ((pow(aRadius1, 2) - pow(aRadius2, 2) + pow(aDistance, 2)) / (2 * aDistance));
        double aHeight = sqrt(pow(aRadius1, 2) - pow(aCut, 2));
        double aX1 = circle1->Center().X(), aX2 = circle2->Center().X();
        double aY1 = circle1->Center().Y(), aY2 = circle2->Center().Y();
        Point aP3 = circle1->Center() + (circle2->Center() - circle1->Center()) * (aCut / aDistance);
        double aAnsX1 = aP3.X() + aHeight / aDistance * (aY2 - aY1);
        double aAnsY1 = aP3.Y() - aHeight / aDistance * (aX2 - aX1);
        double aAnsX2 = aP3.X() - aHeight / aDistance * (aY2 - aY1);
        double aAnsY2 = aP3.Y() + aHeight / aDistance * (aX2 - aX1);
        myInter.emplace_back(aAnsX1, aAnsY1, 0);
        if ( abs(aAnsX1 - aAnsX2) >= TOL && abs(aAnsY1 - aAnsY2) >= TOL )
        {
            myInter.emplace_back(aAnsX2, aAnsY2, 0);
        }
        myStatus = DONE;
    }
    
    
}


void Intersection::InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2)
{
    
    
    if ( IsEquivalent(line1, line2))
    {
        myStatus = EQUAL;
    } else if ( IsParallel(line1, line2))
    {
        myStatus = NOT_INTERSECTED;
    } else
    {
        double aResx, aResy;
        
        double aZn = det(line1->CoefEquation().X(), line1->CoefEquation().Y(),
                         line2->CoefEquation().X(), line2->CoefEquation().Y());
        aResx = -det(line1->CoefEquation().Z(), line1->CoefEquation().Y(),
                     line2->CoefEquation().Z(), line2->CoefEquation().Y()) / aZn;
        aResy = -det(line1->CoefEquation().X(), line1->CoefEquation().Z(),
                     line2->CoefEquation().X(), line2->CoefEquation().Z()) / aZn;
        
        
        myInter.emplace_back(aResx, aResy, 0);
        myStatus = DONE;
    }
}


bool IsParallel(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2)
{
    
    return fabs(det(line1->CoefEquation().X(), line1->CoefEquation().Y(),
                    line2->CoefEquation().X(), line2->CoefEquation().Y())) < EPS;
}

bool IsEquivalent(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2)
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
        return myInter[0];
    return {NAN, NAN, NAN};
}

const Point &Intersection::SecondPoint()
{
    if ( NumberInter() >= 2 )
    {
        return myInter[1];
    }
    return {NAN, NAN, NAN};
    
}

Intersection::InterStatus Intersection::CurrentStatus()
{
    return myStatus;
}

int Intersection::NumberInter()
{
    return myInter.size();
}
