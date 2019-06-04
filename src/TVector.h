#pragma once
#include <TPoint.h>


// Vector can be inherited from a point
// It have coordinates х and у
class TVector:public TPoint
{

  

public:

  //Default constructor (from two numbers)
  TVector(double x_=1, double y_=1) :TPoint(x_, y_) {}

  //Default constructor (from two points)
  TVector(TPoint p1, TPoint p2); 

  //Boolean equals operator
  bool operator==(TVector alt);

  //Division operator
  TVector operator/ (double a);

  //Check vector with zero-vector
  bool IsNull();

  // Get highest common divisor from x and y
  double NOD();

  // Get vector length
  double Interval();
  
};