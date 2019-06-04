#include<Circle.h>

//Default constructor
Circle::Circle(TPoint c, double r_)
{
  if (r_ <= 0) throw - 1;
  centre = c;
  r = r_;
}

//Сopy constructor
Circle::Circle(Circle& alt) 
{
  this->centre = alt.centre;
  this->r = alt.r;
}

//Boolean equals operator
bool Circle::operator==(Circle alt)
{
  double delta_r = alt.GetR() - this->GetR();
  bool center_res = (alt.GetCentre() == this->GetCentre());


  return (abs(delta_r)<EPSILON && center_res);
}

//Finding the coordinate (point) by parameter
TPoint Circle::Coordinate(double t)
{
  double x_t, y_t;

  x_t = r*cos(t) + this->GetCentre().GetX();
  y_t = r*sin(t) + this->GetCentre().GetY();

  TPoint res(x_t, y_t);

  return res;
}

// Finding the tangent vector to the line by the parameter
TVector Circle::TangentVector(double t)
{
  double xd_t, yd_t;

  xd_t = -r*sin(t);
  yd_t = r*cos(t);

  TVector res(xd_t, yd_t);

  return res;

}

//Finding parameter by the point
double Circle::getParam(TPoint alt, int& id)
{
  double res = 0;

  double delta_x = alt.GetX() - this->GetCentre().GetX();
  double delta_y = alt.GetY() - this->GetCentre().GetY();

  double delta_x_degt = delta_x*delta_x;
  double delta_y_degt = delta_y*delta_y;
  double r_degt = this->GetR()*this->GetR();

  if (abs(delta_x_degt + delta_y_degt - r_degt) < EPSILON)
  {
    id = Exist;
    res = atan2(delta_y, delta_x);
  }
  else
    id = NotExist;

  return res;

}

//Get coordinate of centre
TPoint Circle::GetCentre()
{
  return this->centre;
}

//Get radius of circle
double Circle::GetR()
{
  return this->r;
}















