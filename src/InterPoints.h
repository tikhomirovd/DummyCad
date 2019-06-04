#pragma once
#include<Line.h>
#include<Circle.h>
#include<memory>
#include <list>

using namespace std;

//Enumeration of the statuses of finding 
//the points of intersection:
//NonePoints: There are no points of intersection between two curves.
//HavePoints: Two curves have a finite number of intersection points.
//InfinityPoints: Two curves have a infinite number of intersection points.
//CantFindPoints: Unable to find intersection points.
enum status { NonePoints, HavePoints, InfinityPoints, CantFindPoints};


//The class determines the number 
//of intersection points between two curves
class InterPoints
{

protected:

  //List of points of intersection
  list<TPoint> InPnts;

  //Number of intersection points
  int n;

  //Status of finding the points of intersection
  int id;

  //Curves
  shared_ptr<Curve> c1;
  shared_ptr<Curve> c2;


private:

  //Functions for finding points of intersection
  //between curves:

  //Finding two points of intersection
  //between a line and a circle
  void GetPoints(shared_ptr<Circle> a, shared_ptr<Line> alt, TPoint& p1, TPoint& p2);

  //Finding points of intersection
  //between two lines
  void GetIntPointLineLine(shared_ptr<Line> a, shared_ptr<Line> b);

  //Finding points of intersection 
  //between line and circle
  void GetIntPointLineCircle(shared_ptr<Line> a, shared_ptr<Circle> b);

  //Finding points of intersection
  //between two circles
  void GetIntPointCircleCircle(shared_ptr<Circle> a, shared_ptr<Circle> b );


public:

  //Constructor
  InterPoints(shared_ptr<Curve> a, shared_ptr<Curve> b);

  //Get the intersection point parameter 
  //for the first curve by index
  double GetParamC1(int n_p);

  //Get the intersection point parameter 
  //for the second curve by index
  double GetParamC2(int n_p);

  //Get a list of the points of intersection
  const list<TPoint> GetIntPoints();

  //Get the list of intersection point parameters 
  //for the first curve
  list<double> GetParamC1();

  //Get the list of intersection point parameters 
  //for the second curve
  list<double> GetParamC2();

  //Get intersection by index
  TPoint GetIntPoint(int n_p);

  //Get the status of finding 
  //the points of intersection
  int GetStat();

  //Get the number of intersection points
  int GetNumPoints();

};

