#include<InterPoints.h>

//Getting the determinant of a quadratic equation
double Deter(double a, double b, double c)
{
  return b*b - 4 * a*c;
}

//Finding two points of intersection
//between a line and a circle
void InterPoints::GetPoints(shared_ptr<Circle> a, shared_ptr<Line> alt, TPoint& p1, TPoint& p2)
{
  //The coefficients of the quadratic equation
  double a_qe, b_qe, c_qe;

  //Coordinates of points
  double x1, x2;
  double y1, y2;

  //Equation of circle:
  //(x-a1)^2 + (y-b1)^2 = r1^2

  double a1 = a->GetCentre().GetX();
  double b1 = a->GetCentre().GetY();
  double r1 = a->GetR();


  //Equation of line:
  //c2*y = a2*x + b2

  double c2 = alt->TangentVector(0).GetX();
  double a2 = alt->TangentVector(0).GetY();
  double b2 = alt->TangentVector(0).GetX()*alt->Coordinate(0).GetY() - alt->TangentVector(0).GetY()*alt->Coordinate(0).GetX();
  
  //Get a system of two equations:
  //(x-a1)^2 + (y-b1)^2 = r1^2
  //c2*y = a2*x + b2

  //The determinant of a quadratic equation
  double D;

  if (c2 == 0)
  {
    //If c2=0 then 0 = a2*x + b2,
    //It's mean that x = -b2/a2 in intersection points

    //Get the equation:
    // (-b2/a2 - a1)^2 + (y-b1)^2 = r1^2
    // or
    // (b2/a2 + a1)^2 + (y-b1)^2 = r1^2

    double b1_degt = b1*b1;
    double b2_div_a2 = b2 / a2;
    double b2a2_sum_a1 = b2_div_a2 + a1;
    double b2a2a1_degt = b2a2_sum_a1*b2a2_sum_a1;
    double r1_degt = r1*r1;

    //Get quadratic equation:
    //y^2 + y*(-2*b1) + ((b2/a2 + a1)^2 + b1^2 - r1^2) = 0

    a_qe = 1;
    b_qe = -2 * b1;
    c_qe = b1_degt + b2a2a1_degt - r1_degt;

    x1 = -b2_div_a2;
    x2 = x1;

    //Get the determinant of a quadratic equation
    D = Deter(a_qe, b_qe, c_qe);

    //If the determinant is less than zero, 
    //then there are no intersection points
    if (D < 0)
    {
      id = NonePoints;
      return;
    }

    //If the determinant is zero, 
    //then there is only one intersection point,
    //else two
    y1 = (-b_qe + sqrt(D)) / 2 * a_qe;
    y2 = (-b_qe - sqrt(D)) / 2 * a_qe;

  }

  else
  {
    //If c1!=0 then c1*y = a1*x + b1
    //It's mean that y = (a1*x + b1)/c1 in intersection points


    //Get the equation:
    //(x-a1)^2 + ((a1*x + b1)/c1-b1)^2 = r1^2

    double delta_b2c2b1 = b2 / c2 - b1;
    double a2_div_c2 = a2 / c2;
    double c2_degt = c2 * c2;
    double r1_degt = r1 * r1;
    double a2_div_c2_degt = a2_div_c2 * a2_div_c2;
    double a1_degt = a1 * a1;
    double delta_b2c2b1_degt = delta_b2c2b1 * delta_b2c2b1;


    //Get quadratic equation:
    // y^2*(1 + (a2/c2)^2) + 
    //+ y*(2*(a2/c2)*(b2/c2 - b1) - 2*a1) 
    //+ (a1^2 + (b2/c2 - b1)^2 - r1^2) =0


    a_qe = 1 + a2_div_c2_degt;
    b_qe = 2 * a2_div_c2*delta_b2c2b1 - 2 * a1;
    c_qe = a1_degt + delta_b2c2b1_degt - r1_degt;

    //Get the determinant of a quadratic equation
    D = Deter(a_qe, b_qe, c_qe);
    
    //If the determinant is less than zero, 
    //then there are no intersection points
    if (D < 0)
    {
      id = NonePoints;
      return;
    }

    //If the determinant is zero, 
    //then there is only one intersection point,
    //else two
    x1 = (-b_qe + sqrt(D)) / (2 * a_qe);
    x2 = (-b_qe - sqrt(D)) / (2 * a_qe);

    y1 = (a2*x1 + b2) / c2;
    y2 = (a2*x2 + b2) / c2;
  }

  id = HavePoints;
  p1 = TPoint(x1, y1);
  p2 = TPoint(x2, y2);
}

//Finding points of intersection
//between two lines
void InterPoints::GetIntPointLineLine(shared_ptr<Line> a, shared_ptr<Line> b)
{
  //Intersection point
  TPoint res;

  //Intersection point parameter
  double t;

  //If the lines are equal, then they have 
  //an infinite number of intersection points.
  if (a == b)
  {
    id = InfinityPoints;
    n = -1;
    return;
  }

  //If the vectors of lines are equal 
  //(but the lines themselves are not equal), 
  //then they don't have intersection points.
  if (a->TangentVector(0) == b->TangentVector(0))
  {
    id = NonePoints;
    return;
  }

  //Get the system of equations:
  //dir1(x)*t1 + st1(x) = dir2(x)*t2 + st2(x)
  //dir1(y)*t1 + st1(y) = dir2(y)*t2 + st2(y)
  
  //And get:
  //t2 = (dir1(x)*(st2(y) - st1(y)) - dir1(y)*(st2(x) - st1(x))) / (dir1(y)*dir2(x) - dir1(x)*dir2(y))

  double delta_sy = b->Coordinate(0).GetY() - a->Coordinate(0).GetY();
  double delta_sx = b->Coordinate(0).GetX() - a->Coordinate(0).GetX();
  double delta_v = a->TangentVector(0).GetY()*b->TangentVector(0).GetX() - a->TangentVector(0).GetX()*b->TangentVector(0).GetY();
  double delta_s = a->TangentVector(0).GetX()*delta_sy - a->TangentVector(0).GetY()*delta_sx;

  t = delta_s / delta_v;

  n = 1;
  res = b->Coordinate(t);
  id = HavePoints;

  //Put a point in the list 
  //of points of intersection
  InPnts.push_front(res);
}

//Finding points of intersection 
//between line and circle
void InterPoints::GetIntPointLineCircle(shared_ptr<Line> a, shared_ptr<Circle> b)
{

  //Intersection points
  TPoint p1;
  TPoint p2;

  //Find two points of intersection
  //between a line and a circle (see GetPoints)
  GetPoints(b, a, p1, p2);


  //If no points are found, 
  //then there are no intersection points.
  if (id != HavePoints)
    return;

 
  //If two points are equal, 
  //then there is only one intersection point,
  //otherwise two.
  if (p1 == p2)
  {
    n = 1;
    InPnts.push_front(p1);
  }
  else
  {
    n = 2;

    InPnts.push_front(p1);
    InPnts.push_front(p2);
  }

  id = HavePoints;

}


//Finding points of intersection
//between two circles
void InterPoints::GetIntPointCircleCircle(shared_ptr<Circle> a, shared_ptr<Circle> b)
{

  //If two circles are equal, 
  //then there are an infinite number of intersection points.
  if (a == b)
  {
    id = InfinityPoints;
    n = -1;
    return;
  }


  //Get the centers of two circles
  TPoint center_1 = a->GetCentre();
  TPoint center_2 = b->GetCentre();

  //Find the interval between the two centers of the circles.
  double inter = center_1.Interval(center_2);

  
  //If the distance between two circles is greater than the sum of their radii 
  //or if the centers coincide, 
  //then there are no intersection points
  if (inter > a->GetR() + b->GetR() + EPSILON || center_1 == center_2)
  {
    id = NonePoints;
    return;
  }

  //Get the equation:
  //(a1 - a2)*x + (b1 - b2)*y + (c1 - c2) = 0

  double a1 = -2 * a->GetCentre().GetX();
  double b1 = -2 * a->GetCentre().GetY();
  double r1_degt = a->GetR()*a->GetR();
  double c1 = (a1*a1 + b1*b1) / 4 - r1_degt;

  double a2 = -2 * b->GetCentre().GetX();
  double b2 = -2 * b->GetCentre().GetY();
  double r2_degt = b->GetR()*b->GetR();
  double c2 = (a2*a2 + b2*b2) / 4 - r2_degt;


  double delta_a = a1 - a2;
  double delta_b = b1 - b2;
  double delta_c = c1 - c2;

  //This is a chord(line) passing through 
  //the intersection points of the circles.

  shared_ptr<Line> chorda( new Line (-delta_a, delta_b, -delta_c));

  //Find points of intersection 
  //between chord and circle (see GetIntPointLineCircle)
  GetIntPointLineCircle(chorda, b);

}


//Constructor
InterPoints::InterPoints(shared_ptr<Curve> a, shared_ptr<Curve> b)
{
  //Initialize variables
  n = 0;
  c1 = a;
  c2 = b;

  //Determine the type of curve
  shared_ptr<Line> line_a = dynamic_pointer_cast<Line>(a);
  shared_ptr<Line> line_b = dynamic_pointer_cast<Line>(b);

  shared_ptr<Circle> circle_a = dynamic_pointer_cast<Circle>(a);
  shared_ptr<Circle> circle_b = dynamic_pointer_cast<Circle>(b);


  //Call the required function to find 
  //the points of intersection of the curve
  //(or declare "CantFindPoints")
  if (line_a)
  {
    if (line_b)
      GetIntPointLineLine(line_a, line_b);

    else if (circle_b)
      GetIntPointLineCircle(line_a, circle_b);

    else
      id = CantFindPoints;

  }
  else if (circle_a)
  {
    if (line_b)
      GetIntPointLineCircle(line_b, circle_a);
    else if (circle_b)
      GetIntPointCircleCircle(circle_a, circle_b);
    else
      id = CantFindPoints;
  }
  else
    id = CantFindPoints;


}

//Get the intersection point parameter 
//for the first curve by index
double InterPoints::GetParamC1(int n_p)
{
  //Check of correctness of the index
  if (n_p >= n || n_p < 0)
    throw - 1;

  int err;

  //Call of the function of getting the point by index
  //(see GetIntPoint)
  TPoint alt = GetIntPoint(n_p);

  //Determine the type of curve
  shared_ptr<Line> line_c1 = dynamic_pointer_cast<Line>(c1);
  shared_ptr<Circle> circle_c1 = dynamic_pointer_cast<Circle>(c1);

  //Get the parameter
  if (line_c1)
    return line_c1->getParam(alt, err);
  else
    return circle_c1->getParam(alt, err);
}

//Getting the intersection point parameter 
//for the first curve by index
double InterPoints::GetParamC2(int n_p)
{

  //Check of correctness of the index
  if (n_p >= n || n_p < 0)
    throw - 1;

  
  int err;

  //Call of the function of getting the point by index
  //(see GetIntPoint)
  TPoint alt = GetIntPoint(n_p);

  //Determine the type of curve
  shared_ptr<Line> line_c2 = dynamic_pointer_cast<Line>(c2);
  shared_ptr<Circle> circle_c2 = dynamic_pointer_cast<Circle>(c2);

  //Get the parameter
  if (line_c2)
    return line_c2->getParam(alt, err);
  else
    return circle_c2->getParam(alt, err);
}


//Get a list of the points of intersection
const list<TPoint> InterPoints::GetIntPoints()
{
  return InPnts;
}

//Getting the list of intersection point parameters 
//for the first curve
list<double> InterPoints::GetParamC1()
{
  list<double> res;

  //Check of for the existence of intersection points
  if (id != HavePoints)
    return res;

  //Determine the type of curve
  shared_ptr<Line> line_c1 = dynamic_pointer_cast<Line>(c1);
  shared_ptr<Circle> circle_c1 = dynamic_pointer_cast<Circle>(c1);

  int err;

  //Get the list of intersection point parameters
  if (line_c1)
    for (int i = 0; i<n;i++)
     res.push_back(line_c1->getParam(this->GetIntPoint(i), err));
  else
    for (int i = 0; i<n;i++)
      res.push_back(circle_c1->getParam(this->GetIntPoint(i), err));

  return res;
}


//Get the list of intersection point parameters 
//for the second curve
list<double> InterPoints::GetParamC2()
{

  list<double> res;

  //Check of for the existence of intersection points
  if (id != HavePoints)
    return res;

  //Determine the type of curve
  shared_ptr<Line> line_c2 = dynamic_pointer_cast<Line>(c2);
  shared_ptr<Circle> circle_c2 = dynamic_pointer_cast<Circle>(c2);

  int err;

  //Get the list of intersection point parameters
  if (line_c2)
    for (int i = 0; i<n;i++)
      res.push_back(line_c2->getParam(this->GetIntPoint(i), err));
  else
    for (int i = 0; i<n;i++)
      res.push_back(circle_c2->getParam(this->GetIntPoint(i), err));

  return res;
}


//Get the point of intersection by index
TPoint InterPoints::GetIntPoint(int n_p)
{
  //Check of correctness of the index
  if (n_p >= n || n_p < 0)
    throw - 1;
  

  //Creating a copy of the list of points of intersection
  list<TPoint> alt = InPnts;

  //Get the point of intersection
  for (int i = 0; i < n_p; i++)
    alt.pop_front();

  return alt.front();

}

//Get the status of finding 
//the points of intersection
int InterPoints::GetStat()
{
  return id;
}

//Get the number of intersection points
int InterPoints::GetNumPoints()
{
  return n;
}


