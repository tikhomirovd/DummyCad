#include<TPoint.h>


//Default constructor
TPoint::TPoint(double x_, double y_)
{
  x = x_;
  y = y_;
}


//Сopy constructor
TPoint::TPoint(const TPoint& alt)
{
  this->x = alt.x;
  this->y = alt.y;
}


//Boolean equals operator
bool TPoint::operator==(TPoint alt)
{
  double delta_x = this->GetX() - alt.GetX();
  double delta_y = this->GetY() - alt.GetY();
  return (abs(delta_x)<EPSILON && abs(delta_y)<EPSILON);
}


//Assignment operator
TPoint& TPoint::operator=(TPoint alt)
{
  this->x = alt.x;
  this->y = alt.y;
  return *this;
}


//Get coordinate x
double TPoint::GetX()
{
  return this->x;
}


//Get coordinate y
double TPoint::GetY()
{
  return this->y;
}


//Get interval between two points
double TPoint::Interval(TPoint alt)
{
  double res;

  double delta_x = alt.GetX() - this->GetX();
  double delta_y = alt.GetY() - this->GetY();

  double delta_x_degt = delta_x*delta_x;
  double delta_y_degt = delta_y*delta_y;

  res = sqrt(delta_x_degt + delta_y_degt);

  return res;

}
