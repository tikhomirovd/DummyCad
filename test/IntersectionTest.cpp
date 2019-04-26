// GoogleTest includes
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#include <gtest/gtest.h>

#include <vector>
#include <memory>

#include <Intersection.h>
#include <Curve.h>
#include <Vector.h>
#include <Straight.cpp>
#include <Circle.cpp>
#include <Point.h>

#define M_PI 3.141592653589793
#define EPS 1e-10

static const double THE_TOLERANCE = 1.e-7;

// одна точка пересечения двух прямых 
TEST(LineLineTest, OneSolution_01)
{
  shared_ptr<Curve> straid1 = shared_ptr<Straight>(new Straight(0.0, 0.0, 1.0, 0.0));
  shared_ptr<Curve> straid2 = shared_ptr<Straight>(new Straight(0.0, 0.0, 0.0, 1.0));
  
  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(straid1,straid2);
  
  ASSERT_EQ(points.size(), 1);
  ASSERT_NEAR(points[0].getX(), 0.0, THE_TOLERANCE);
  ASSERT_NEAR(points[0].getY(), 0.0, THE_TOLERANCE);
}

// одна точка пересечения двух прямых 
TEST(LineLineTest, OneSolution_02)
{
	shared_ptr<Curve> straid1 = shared_ptr<Straight>(new Straight(2.0, 0.0, 0.0, 2.0));
	shared_ptr<Curve> straid2 = shared_ptr<Straight>(new Straight(0.0, -1.0, 2.0, 0.0));

	Intersections intersection;
	std::vector<Point> points = intersection.Intersection(straid1, straid2);

	ASSERT_EQ(points.size(), 1);
	ASSERT_NEAR(points[0].getX(), 2.0, THE_TOLERANCE);
	ASSERT_NEAR(points[0].getY(), -1.0, THE_TOLERANCE);
}

//нет точек пересечения прямых
TEST(LineLineTest, ZeroSolutions_03)
{
  double A = 5.0, B = 0.0, C = 1.0, D = 0.0;
  
  shared_ptr<Curve> straid1 = shared_ptr<Straight>(new Straight(A, B, C, D));
  shared_ptr<Curve> straid2 = shared_ptr<Straight>(new Straight(A, C, B, D));
  
  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(straid1,straid2);
  
  ASSERT_EQ(points.size(), 0);
}
 
//две точки пересечения прямой и окружности
TEST(LineCircleTest, TwoSolution_00001)
{
  shared_ptr<Curve> straid1 = shared_ptr<Straight>(new Straight(2.0, 0.0, 0.0, 2.0));
  shared_ptr<Curve> circle1 = shared_ptr<Circle>(new Circle(2.0, 1.0, 3.0));

  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(straid1,circle1);

  ASSERT_EQ(points.size(), 2);
  ASSERT_NEAR(points[0].getX(), 2.0, THE_TOLERANCE); 
  ASSERT_NEAR(points[0].getY(), -2.0, THE_TOLERANCE); 
  ASSERT_NEAR(points[1].getX(), 2.0, THE_TOLERANCE);
  ASSERT_NEAR(points[1].getY(), 4.0, THE_TOLERANCE); 
} 
//одна точка пересечения прямой и окуржности
TEST(LineCircleTest, OneSolution_00002)
{ 
  shared_ptr<Curve> straid1 = shared_ptr<Straight>(new Straight(0.0, 3.0, 5.0, 0.0));
  shared_ptr<Curve> circle1 = shared_ptr<Circle>(new Circle(2.0, 0.0, 3.0));
  
  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(straid1, circle1);;

  ASSERT_EQ(points.size(), 1);
  ASSERT_NEAR(points[0].getX(), 2.0, THE_TOLERANCE); 
  ASSERT_NEAR(points[0].getY(), 3.0, THE_TOLERANCE); 
}      

//нет точек пересечения прямой и окружности
TEST(LineCircleTest, ZeroSolution_00003)
{
  double A = 6.0, B = 0.0, C = 0.0, D = 3.0, E = 2.0;
  shared_ptr<Curve> straid1 = shared_ptr<Straight>(new Straight(A, B, C, D));
  shared_ptr<Curve> circle1 = shared_ptr<Circle>(new Circle(E, C, D));
  
  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(straid1,circle1);

  ASSERT_EQ(points.size(), 0);
}   

//две точки пересечения окружностей
TEST(CircleCircleTest, TwoSolutions_1)
{
  shared_ptr<Curve> circle1 = shared_ptr<Circle>(new Circle(5, 4, 3));
  shared_ptr<Curve> circle2 = shared_ptr<Circle>(new Circle(9, 7, 3));
  
  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(points.size(), 2);
  // найти точки пересечения двух окружностей
  ASSERT_NEAR(points[0].getX(), 6.2478601953663899, THE_TOLERANCE);
  ASSERT_NEAR(points[0].getY(), 6.5028530728448137, THE_TOLERANCE);  
  ASSERT_NEAR(points[1].getX(), 7.7521398046336101, THE_TOLERANCE); 
  ASSERT_NEAR(points[1].getY(), 4.4971469271551863, THE_TOLERANCE); 
} 

//одна точка пересечения окружностей
TEST(CircleCircleTest, OneSolutions_2)
{
  double A = 3.0, B = 0.0, C = 3.0, D = 9.0;
  
  shared_ptr<Curve> circle2 = shared_ptr<Circle>(new Circle(A, B, C));
  shared_ptr<Curve> circle1 = shared_ptr<Circle>(new Circle(D, B, C));
  
  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(points.size(), 1);
  ASSERT_NEAR(points[0].getX(), 6.0, THE_TOLERANCE); 
  ASSERT_NEAR(points[0].getY(), 0.0, THE_TOLERANCE); 
}

//нет точек пересечения у двух окружностей
/*TEST(CircleCircleTest, ZeroSolutions_3)
{
  double A = 3.0, B = 0.0, C = 3.0, D = 9.0, E = 2.0;
  
  shared_ptr<Curve> circle2 = shared_ptr<Circle>(new Circle(A, B, E));
  shared_ptr<Curve> circle1 = shared_ptr<Circle>(new Circle(D, B, C));
  
  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(points.size(), 0);
}  */

//концентрич-е окружности разного радиуса
TEST(CircleCircleTest, OneSolutions_001)
{
  double A = 4.0, B = 1.0, C = 0.0, D = 3.0;
  
  shared_ptr<Curve> circle2 = shared_ptr<Circle>(new Circle(A, C, B));
  shared_ptr<Curve> circle1 = shared_ptr<Circle>(new Circle(A, C, D));
  
  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(points.size(), 0); 
} 

//концентрич-е окружности одинакового радиуса
TEST(CircleCircleTest, OneSolutions_002)
{
  double A = 4.0, B = 1.0, C = 0.0; 
  
  shared_ptr<Curve> circle2 = shared_ptr<Circle>(new Circle(A, C, B));
  shared_ptr<Curve> circle1 = shared_ptr<Circle>(new Circle(A, C, B));
  
  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(circle1, circle2);
 //?
  ASSERT_EQ(points.size(), 0); 
} 

//окружность в окружности
/*TEST(CircleCircleTest, OneSolutions_003)
{
  double A = 4.0, B = 2.0, C = 0.0; 
  
  shared_ptr<Curve> circle2 = shared_ptr<Circle>(new Circle(A, C, A));
  shared_ptr<Curve> circle1 = shared_ptr<Circle>(new Circle(B, C, B));
  
  Intersections intersection;
  std::vector<Point> points = intersection.Intersection(circle1, circle2);
 //?
  ASSERT_EQ(points.size(), 1);
  ASSERT_NEAR(points[0].getX(), 0.0, THE_TOLERANCE);
  ASSERT_NEAR(points[0].getY(), 0.0, THE_TOLERANCE);
}  */

/* 
TEST(EquationTest, ThrowWrongIndex)
{
  double A = 1.0, B = 1.0, C = 2.0;
  SquareEquation anEq(A, B, C);

  ASSERT_EQ(anEq.NbSolutions(), 0);
  ASSERT_ANY_THROW(anEq.Solution(0));
}   */



//=============================================================================
//function : main
//purpose  :
//=============================================================================
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
