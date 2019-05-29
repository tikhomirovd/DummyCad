// GoogleTest includes
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#include <gtest/gtest.h>

// Includes from STL.
#include <vector>
#include <memory>

// Includes from Core.
#include <Intersection.h>
#include <Curve.h>
#include <Vector.h>
#include <Point.h>
#include <Line.h>
#include <Circle.h>

static const double M_PI = 3.141592653589793;
static const double EPS = 1.e-10;

// Определяется допуск для решений.
static const double THE_TOLERANCE = 1.e-7;

// Одна точка пересечения двух прямых
TEST(LineLineTest, OneSolution_01)
{
  std::shared_ptr<Curve> straid1 = std::shared_ptr<Line>(new Line(0.0, 0.0, Vector(1.0, 0.0)));
  std::shared_ptr<Curve> straid2 = std::shared_ptr<Line>(new Line(0.0, 0.0, Vector(0.0, 1.0)));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(straid1, straid2);

  ASSERT_EQ(result->type, SOLUTION);
  ASSERT_EQ(result->solution.size(), 1);
  ASSERT_NEAR(result->solution[0].getX(), 0.0, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[0].getY(), 0.0, THE_TOLERANCE);
}

// Одна точка пересечения двух прямых 
TEST(LineLineTest, OneSolution_02)
{
  std::shared_ptr<Curve> straid1 = std::shared_ptr<Line>(new Line(2.0, 0.0, Vector(0.0, 2.0)));
  std::shared_ptr<Curve> straid2 = std::shared_ptr<Line>(new Line(0.0, -1.0, Vector(2.0, 0.0)));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(straid1, straid2);

  ASSERT_EQ(result->solution.size(), 1);
  ASSERT_NEAR(result->solution[0].getX(), 2.0, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[0].getY(), -1.0, THE_TOLERANCE);
}

// Нет точек пересечения прямых
TEST(LineLineTest, ZeroSolutions_03)
{
  std::shared_ptr<Curve> straid1 = std::shared_ptr<Line>(new Line(0.0, 5.0, Vector(1.0, 0.0)));
  std::shared_ptr<Curve> straid2 = std::shared_ptr<Line>(new Line(0.0, 3.0, Vector(1.0, 0.0)));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(straid1, straid2);

  ASSERT_EQ(result->solution.size(), 0);
}

// Прямые совпадают
TEST(LineLineTest, ZeroSolutions_04)
{
  std::shared_ptr<Curve> straid1 = std::shared_ptr<Line>(new Line(0.0, 5.0, Vector(1.0, 0.0)));
  std::shared_ptr<Curve> straid2 = std::shared_ptr<Line>(new Line(0.0, 5.0, Vector(1.0, 0.0)));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(straid1, straid2);

  ASSERT_EQ(result->solution.size(), 0);
}

// Две точки пересечения прямой и окружности
TEST(LineCircleTest, TwoSolutions_05)
{
  std::shared_ptr<Curve> straid1 = std::shared_ptr<Line>(new Line(2.0, 0.0, Vector(0.0, 2.0)));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(2.0, 1.0, 3.0));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(straid1, circle1);

  ASSERT_EQ(result->solution.size(), 2);
  ASSERT_NEAR(result->solution[0].getX(), 2.0, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[0].getY(), -2.0, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[1].getX(), 2.0, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[1].getY(), 4.0, THE_TOLERANCE);
}

// Одна точка пересечения прямой и окуржности
TEST(LineCircleTest, OneSolution_06)
{
  std::shared_ptr<Curve> straid1 = std::shared_ptr<Line>(new Line(0.0, 3.0, Vector(5.0, 0.0)));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(2.0, 0.0, 3.0));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(straid1, circle1);;

  ASSERT_EQ(result->solution.size(), 1);
  ASSERT_NEAR(result->solution[0].getX(), 2.0, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[0].getY(), 3.0, THE_TOLERANCE);
}

// Нет точек пересечения прямой и окружности
TEST(LineCircleTest, ZeroSolutions_07)
{
  double A = 6.0, B = 0.0, C = 0.0, D = 3.0, E = 2.0;

  std::shared_ptr<Curve> straid1 = std::shared_ptr<Line>(new Line(A, B, Vector(C, D)));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(E, C, D));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(straid1, circle1);

  ASSERT_EQ(result->solution.size(), 0);
}

// Две точки пересечения окружностей
TEST(CircleCircleTest, TwoSolutions_08)
{
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(5, 4, 3));
  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(9, 7, 3));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(result->solution.size(), 2);
  ASSERT_NEAR(result->solution[0].getX(), 6.2478601953663899, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[0].getY(), 6.5028530728448137, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[1].getX(), 7.7521398046336101, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[1].getY(), 4.4971469271551863, THE_TOLERANCE);
}

// Одна точка пересечения окружностей
TEST(CircleCircleTest, OneSolution_09)
{
  double A = 3.0, B = 0.0, C = 3.0, D = 9.0;

  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(A, B, C));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(D, B, C));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(result->solution.size(), 1);
  ASSERT_NEAR(result->solution[0].getX(), 6.0, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[0].getY(), 0.0, THE_TOLERANCE);
}

// Одна точка пересечения окружностей с нецелочисленными радиусами
TEST(CircleCircleTest, OneSolution_10)
{
  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(3.0, 0.0, 3.5));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(9.0, 0.0, 2.5));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(result->solution.size(), 1);
  ASSERT_NEAR(result->solution[0].getX(), 6.5, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[0].getY(), 0.0, THE_TOLERANCE);
}

// Нет точек пересечения у двух окружностей
TEST(CircleCircleTest, ZeroSolutions_11)
{
  double A = 3.0, B = 0.0, C = 3.0, D = 9.0, E = 2.0;

  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(A, B, E));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(D, B, C));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(result->solution.size(), 0);
}

// Концентрич-е окружности разного радиуса
TEST(CircleCircleTest, OneSolution_12)
{
  double A = 4.0, B = 1.0, C = 0.0, D = 3.0;

  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(A, C, B));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(A, C, D));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(result->solution.size(), 0);
}

// Концентрич-е окружности одинакового радиуса
TEST(CircleCircleTest, OneSolution_13)
{
  double A = 4.0, B = 1.0, C = 0.0;

  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(A, C, B));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(A, C, B));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(circle1, circle2);
  ASSERT_EQ(result->solution.size(), 0);
}

// Окружность в окружности
TEST(CircleCircleTest, OneSolution_14)
{
  double A = 4.0, B = 2.0, C = 0.0;

  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(A, C, A));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(B, C, B));

  Intersections intersection;
  std::shared_ptr<CalculationResult> result = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(result->solution.size(), 1);
  ASSERT_NEAR(result->solution[0].getX(), 0.0, THE_TOLERANCE);
  ASSERT_NEAR(result->solution[0].getY(), 0.0, THE_TOLERANCE);
}

// Неизвестный тип кривой
TEST(CircleCircleTest, UnsupportedCurve_15)
{
  class DummyCurve : public Curve
  {
  public:
    DummyCurve(double x, double y)
      : Curve(x, y)
    {
    }

    virtual Point PointCalcul(double t) const override { return Point(0, 0); };
    virtual Vector Gradient(double t) const override { return Vector(0, 0); };
    bool ClosedCurve() const override { return true; };

  };
  double A = 4.0, C = 0.0;

  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(A, C, A));
  std::shared_ptr<Curve> dummy = std::shared_ptr<DummyCurve>(new DummyCurve(A, C));

  Intersections intersection;
  ASSERT_NO_THROW(intersection.Intersection(dummy, circle2));
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
