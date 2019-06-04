#include <Line.h>

//Default constructor
Line::Line(TPoint st_, TVector dir_)
{
  if (dir_.IsNull())
    throw - 1;
  this->st = st_;
  this->dir = dir_;
}

//Constructor of line from formula:
//by=ax+c
Line::Line(double a, double b, double c)
{
  if (a == 0 && b == 0)
    throw - 1;

  TVector alt_dir(b, a);

  TPoint alt_st;
  if (a != 0)
    alt_st = TPoint(-c / a, 0);
  else
    alt_st = TPoint(0, c / b);

  dir = alt_dir;
  st = alt_st;


}

//Сopy constructor
Line::Line(Line& alt)
{
  this->st = alt.st;
  this->dir = alt.dir;
}

//Boolean equals operator
bool Line::operator==(Line alt)
{

  bool vect = this->dir == alt.dir;
  if (vect)
  {
    TVector res(this->st, alt.st);
    return this->dir == res;
  }
  
  return vect;
    
}

//Finding the coordinate (point) by parameter
TPoint Line::Coordinate(double t)
{
  double x_t, y_t;

  x_t = st.GetX() + dir.GetX()*t;
  y_t = st.GetY() + dir.GetY()*t;

  TPoint res(x_t, y_t);

  return res;
}

//Finding the parameter by the point
double Line::getParam(TPoint alt , int& id)
{
  double delta_x = alt.GetX() - this->st.GetX();
  double delta_y = alt.GetY() - this->st.GetY();

  double tx = this->dir.GetY()*delta_x;
  double ty = this->dir.GetX()*delta_y;

  if (abs(tx - ty) > EPSILON)
  {
    id = NotExist;
    return 0.0;
  }

  id = Exist;

  if (this->dir.GetX() == 0)
    return delta_y / this->dir.GetY();
  else 
    return delta_x / this->dir.GetX();
 

}

//Finding the tangent vector to the line by the parameter
TVector Line::TangentVector(double t)
{
  return dir;
}


