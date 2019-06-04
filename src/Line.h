#pragma once
#include<Curve.h>

//Line has the form
//x=dir(x)*t+st(x)
//y=dir(y)*t+st(y)
class Line : public Curve
{

protected:
  TPoint st;
  TVector dir;

public:

  //Default constructor
  Line(TPoint st_ = TPoint(0,0), TVector dir_ = TVector(1,1)); 
  
  //Constructor of line from formula:
  //by=ax+c
  Line(double a=1, double=0, double c=0); 

  //Сopy constructor
  Line(Line& alt);

  //Boolean equals operator
  bool operator==(Line alt);

  //Finding the coordinate (point) by parameter
  TPoint Coordinate(double t=0);

  //Finding the parameter by the point
  double getParam(TPoint alt, int& id);

  //Finding the tangent vector to the line by the parameter
  TVector TangentVector(double t=0);

  //Test on Curve Closure
  bool IsClosed()
  {
    return false;
  }

  
};