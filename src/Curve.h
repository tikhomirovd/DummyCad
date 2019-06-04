#pragma once
#include "Defines.h"
#include <TVector.h>


//Enumeration of the existence of a point on a curve:
//NotExist: Point is not on a curve
//Exist: Point is on a curve
enum st { NotExist, Exist};


//Abstract class "curve"
class Curve
{
public:

  //Finding coordinate (point) by parameter
  virtual TPoint Coordinate(double t) = 0;

  //Finding the tangent vector to the curve by the parameter
  virtual TVector TangentVector(double t) = 0; 


  //Finding parameter by the point
  virtual double getParam(TPoint alt, int& id) = 0; 

  //Test on Curve Closure
  virtual bool IsClosed()=0;  
};