#pragma once
#include<cmath>
#define EPSILON 0.000000001

//Point have coordinates х and у
class TPoint
{
protected:

  double x;
  double y;

public:

  //Default constructor
  TPoint(double x_=0, double y_=0);

  //Сopy constructor
  TPoint(const TPoint& alt); 

  //Boolean equals operator
  bool operator==(TPoint alt);

  //Assignment operator
  TPoint& operator=(TPoint alt); 

  //Get coordinate x
  double GetX();

  //Get coordinate y
  double GetY();

  //Get interval between two points
  double Interval(TPoint alt);
};
