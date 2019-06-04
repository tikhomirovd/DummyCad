#pragma once
#include<Curve.h>
#include <Line.h>


//Circle has the form 
//x=r*cost+c(x)
//y=r*sint+c(y)
class Circle : public Curve
{
protected:

  TPoint centre;
  double r;

public:

  //Default constructor
  Circle(TPoint c=TPoint(), double r_ = 1);

  //Сopy constructor
  Circle(Circle& alt);

  //Boolean equals operator
  bool operator==(Circle alt);

  //Finding the coordinate (point) by parameter
  TPoint Coordinate(double t);

  // Finding the tangent vector to the line by the parameter
  TVector TangentVector(double t);

  //Finding parameter by the point
  double getParam(TPoint alt, int& id);

  //Get coordinate of centre
  TPoint GetCentre();

  //Get radius of circle
  double GetR();

  //Test on Curve Closure
  bool IsClosed()
  {
    return true;
  }

  
};