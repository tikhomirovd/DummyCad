#include <TVector.h>


//Default constructor (from two points)
TVector::TVector(TPoint p1, TPoint p2)
{
  x = p2.GetX() - p1.GetX();
  y = p2.GetY() - p1.GetY();
}


//Boolean equals operator
bool TVector::operator==(TVector alt)
{
  return (this->x*alt.y == alt.x*this->y);
}


//Division operator
TVector TVector::operator/(double a)
{
  double res_x, res_y;
  TVector res;

  res_x = this->GetX() / a;
  res_y = this->GetY() / a;

  res = TVector(res_x, res_y);
  return res;

}


//Check vector with zero-vector
bool TVector::IsNull()
{
  return (this->x == 0 && this->y == 0);
}


// Get highest common divisor from x and y
double TVector::NOD()
{
  
  double a = abs(this->GetX());
  double b = abs(this->GetY());
  while (a != 0 && b != 0)
  {
    if (a < b)
      while (a <= b)
        b = b - a;

    else
      while (b <= a)
        a = a - b;
  }
  if (a != 0)
    return a;
  else
    return b;

}


// Get vector length
double TVector::Interval()
{
  double res;

  double x_degt = this->GetX()*this->GetX();
  double y_degt = this->GetY()*this->GetY();

  res = sqrt(x_degt + y_degt);

  return res;
}