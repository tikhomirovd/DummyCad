#include <Curve.h>
#include <Circle.h>
#include<InterPoints.h>
#include<iostream>


void showerr(int er)
{
  switch (er)
  {
  case 0:
    cout << "NonePoints" << '\n';
    break;
  case 1:
    cout << "HavePoints";
    break;
  case 2:
    cout << "InfinityPoints" << '\n';
    break;
  default:
    cout << "unused error";
    break;
  }
  cout << '\n';
}


void showPoint(TPoint alt)
{
  cout << '(' << alt.GetX() << ',' << alt.GetY() << ")\n";
}

void showParam(double t)
{
  cout << "t = " << t << '\n';
}

int main()
{
  //LineLine
  TPoint a_p(0, 0);
  TVector a_v(1, 1);

  shared_ptr <Line> a (new Line (a_p, a_v));


  TPoint b_p(3, -1);
  TVector b_v(-1, 1);

  shared_ptr <Line> b (new Line(b_p, b_v));

  InterPoints a_b(a, b);

  showerr(a_b.GetStat());

 
  showPoint(a_b.GetIntPoint(0));



  showParam(a_b.GetParamC1(0));
  showParam(a_b.GetParamC2(0));

  //LineCircle
  cout << '\n';
  TPoint l_p;
  TVector l_v(1, 1);
  shared_ptr<Line> l(new Line(l_p, l_v));

  TPoint c_c(1, 1);
  double c_r = 1;
  shared_ptr<Circle> c(new Circle(c_c, c_r));
  
  InterPoints c_l(c, l);

 
  showPoint(c_l.GetIntPoint(0));



  showParam(c_l.GetParamC1(0));
  showParam(c_l.GetParamC2(0));

  cout << '\n';

  showPoint(c_l.GetIntPoint(1));



  showParam(c_l.GetParamC1(1));
  showParam(c_l.GetParamC2(1));


  //CircleCircle

  cout << '\n';

  TPoint c1_c(5,3);
  double c1_r = 5;
  shared_ptr<Circle> c1(new Circle(c1_c, c1_r));

  TPoint c2_c(1,3);
  double c2_r = 3;
  shared_ptr<Circle> c2(new Circle(c2_c, c2_r));

  InterPoints c1_c2(c1, c2);

  showerr(c1_c2.GetStat());
  showPoint(c1_c2.GetIntPoint(0));
  showPoint(c1_c2.GetIntPoint(1));

  return 0;
}