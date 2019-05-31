#include <gtest/gtest.h>

#include <memory>

#include <Circle.h>
#include <Intersection.h>
#include <Curve.h>
#include <Vector.h>
#include <Point.h>
#include <Line.h>

#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Point.hxx>
#include <Geom2d_Vector.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Geometry.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

static const double THE_TOLERANCE = 1.e-7;

// метод пересечения двух линий и сравнение полученных решений (одна точка пересечения)
TEST(Line, SolutionForOCCT_1)
{
  // задание линии1 OCCT
  Geom2d_Line aLineFirst = Geom2d_Line(gp_Pnt2d(0.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0)));
  // задание линии2 OCCT
  Geom2d_Line aLineSecond = Geom2d_Line(gp_Pnt2d(0.0, 0.0), gp_Dir2d(gp_Vec2d(0.0, 1.0)));

  Handle(Geom2d_Line) aLine1 = new Geom2d_Line(aLineFirst);
  Handle(Geom2d_Line) aLine2 = new Geom2d_Line(aLineSecond);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aLine1, aLine2);

  gp_Pnt2d rez = result.Point(1);

  // задание линий моего метода
  std::shared_ptr<Curve> line1 = std::shared_ptr<Line>(new Line(0.0, 0.0, Vector(1.0, 0.0)));
  std::shared_ptr<Curve> line2 = std::shared_ptr<Line>(new Line(0.0, 0.0, Vector(0.0, 1.0)));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(line1, line2);

  ASSERT_NEAR(results->solution[0].getX(), rez.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[0].getY(), rez.Y(), THE_TOLERANCE);
}

// Пересечение окружности и прямой / сравнение решения (две точки)
TEST(LineCircle, SolutionForOCCT_2)
{
  // задание окружности1 OCCT
  Geom2d_Circle aCircleOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(2.0, 1.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);
  // задание линии OCCT
  Geom2d_Line aLineOCCT = Geom2d_Line(gp_Pnt2d(2.0, 0.0), gp_Dir2d(gp_Vec2d(0.0, 2.0)));

  Handle(Geom2d_Circle) aCircleOCCT1 = new Geom2d_Circle(aCircleOCCT);
  Handle(Geom2d_Line) aLine1 = new Geom2d_Line(aLineOCCT);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aCircleOCCT1, aLine1);

  gp_Pnt2d rez1 = result.Point(1);
  gp_Pnt2d rez2 = result.Point(2);

  // задание линии моего метода
  std::shared_ptr<Curve> line = std::shared_ptr<Line>(new Line(2.0, 0.0, Vector(0.0, 2.0)));
  // задание окружности моего метода
  std::shared_ptr<Curve> circle = std::shared_ptr<Circle>(new Circle(2.0, 1.0, 3.0));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(line, circle);

  ASSERT_NEAR(results->solution[1].getX(), rez1.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[1].getY(), rez1.Y(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[0].getX(), rez2.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[0].getY(), rez2.Y(), THE_TOLERANCE);
}

// точка, заданная по умолчанию
TEST(Line, SolutionForOCCT_3)
{
  // задание точки
  gp_Pnt2d aPointFirst;

  ASSERT_NEAR(aPointFirst.X(), 0.0, THE_TOLERANCE);
  ASSERT_NEAR(aPointFirst.Y(), 0.0, THE_TOLERANCE);
}

// Две точки пересечения окружностей
TEST(CircleCircle, SolutionForOCCT_4)
{

  Geom2d_Circle aCircleOCCT1 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(5.0, 4.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);
  Geom2d_Circle aCircleOCCT2 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(9.0, 7.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);

  Handle(Geom2d_Circle) aCircleOCCTNew1 = new Geom2d_Circle(aCircleOCCT1);
  Handle(Geom2d_Circle) aCircleOCCTNew2 = new Geom2d_Circle(aCircleOCCT2);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aCircleOCCTNew1, aCircleOCCTNew2);

  gp_Pnt2d rez1 = result.Point(1);
  gp_Pnt2d rez2 = result.Point(2);

  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(5, 4, 3));
  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(9, 7, 3));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(circle1, circle2);

  ASSERT_NEAR(results->solution[1].getX(), rez1.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[1].getY(), rez1.Y(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[0].getX(), rez2.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[0].getY(), rez2.Y(), THE_TOLERANCE);
  }

// Одна точка пересечения окружностей
TEST(CircleCircle, SolutionForOCCT_5)
{
  Geom2d_Circle aCircleOCCT1 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(3.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);
  Geom2d_Circle aCircleOCCT2 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(9.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);

  Handle(Geom2d_Circle) aCircleOCCTNew1 = new Geom2d_Circle(aCircleOCCT1);
  Handle(Geom2d_Circle) aCircleOCCTNew2 = new Geom2d_Circle(aCircleOCCT2);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aCircleOCCTNew1, aCircleOCCTNew2);

  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(3.0, 0.0, 3.0));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(9.0, 0.0, 3.0));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(circle1, circle2);

  gp_Pnt2d rez1 = result.Point(1);

  ASSERT_NEAR(results->solution[0].getX(), rez1.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[0].getY(), rez1.Y(), THE_TOLERANCE);
}
