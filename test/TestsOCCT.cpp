﻿#include <gtest/gtest.h>

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
#include <Geom2dAPI_InterCurveCurve.hxx>

static const double THE_TOLERANCE = 1.e-7;

// метод пересечения двух линий и сравнение полученных решений (одна точка пересечения)
TEST(LineLine, SolutionForOCCT_1)
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

// Нет пересечения двух линий / сравнение решения
TEST(LineLine, SolutionForOCCT_2)
{
  // задание линии1 OCCT
  Geom2d_Line aLineFirst = Geom2d_Line(gp_Pnt2d(0.0, 5.0), gp_Dir2d(gp_Vec2d(1.0, 0.0)));
  // задание линии2 OCCT
  Geom2d_Line aLineSecond = Geom2d_Line(gp_Pnt2d(0.0, 3.0), gp_Dir2d(gp_Vec2d(1.0, 0.0)));

  Handle(Geom2d_Line) aLine1 = new Geom2d_Line(aLineFirst);
  Handle(Geom2d_Line) aLine2 = new Geom2d_Line(aLineSecond);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aLine1, aLine2);

  // задание линий моего метода
  std::shared_ptr<Curve> line1 = std::shared_ptr<Line>(new Line(0.0, 5.0, Vector(1.0, 0.0)));
  std::shared_ptr<Curve> line2 = std::shared_ptr<Line>(new Line(0.0, 3.0, Vector(1.0, 0.0)));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(line1, line2);

  ASSERT_EQ(results->solution.size(), result.NbPoints());
}

// Линии совпадают / сравнение решения
TEST(LineLine, SolutionForOCCT_3)
{
  // задание линии1 OCCT
  Geom2d_Line aLineFirst = Geom2d_Line(gp_Pnt2d(0.0, 5.0), gp_Dir2d(gp_Vec2d(1.0, 0.0)));
  // задание линии2 OCCT
  Geom2d_Line aLineSecond = Geom2d_Line(gp_Pnt2d(0.0, 5.0), gp_Dir2d(gp_Vec2d(1.0, 0.0)));

  Handle(Geom2d_Line) aLine1 = new Geom2d_Line(aLineFirst);
  Handle(Geom2d_Line) aLine2 = new Geom2d_Line(aLineSecond);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aLine1, aLine2);

  // задание линий моего метода
  std::shared_ptr<Curve> line1 = std::shared_ptr<Line>(new Line(0.0, 5.0, Vector(1.0, 0.0)));
  std::shared_ptr<Curve> line2 = std::shared_ptr<Line>(new Line(0.0, 5.0, Vector(1.0, 0.0)));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(line1, line2);

  ASSERT_EQ(results->solution.size(), result.NbPoints());
}

// Пересечение окружности и прямой / сравнение решения (две точки)
TEST(LineCircle, SolutionsForOCCT_4)
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

// Пересечение окружности и прямой / сравнение решения (одна точка)
TEST(LineCircle, SolutionsForOCCT_5)
{
  // задание окружности1 OCCT
  Geom2d_Circle aCircleOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(2.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);
  // задание линии OCCT
  Geom2d_Line aLineOCCT = Geom2d_Line(gp_Pnt2d(0.0, 3.0), gp_Dir2d(gp_Vec2d(5.0, 0.0)));

  Handle(Geom2d_Circle) aCircleOCCT1 = new Geom2d_Circle(aCircleOCCT);
  Handle(Geom2d_Line) aLine1 = new Geom2d_Line(aLineOCCT);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aCircleOCCT1, aLine1);

  gp_Pnt2d rez1 = result.Point(1);

  std::shared_ptr<Curve> line = std::shared_ptr<Line>(new Line(0.0, 3.0, Vector(5.0, 0.0)));
  std::shared_ptr<Curve> circle = std::shared_ptr<Circle>(new Circle(2.0, 0.0, 3.0));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(line, circle);

  ASSERT_NEAR(results->solution[0].getX(), rez1.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[0].getY(), rez1.Y(), THE_TOLERANCE);
}

// Нет пересечения окружности и прямой / сравнение решения
TEST(LineCircle, SolutionsForOCCT_6)
{
  // задание окружности1 OCCT
  Geom2d_Circle aCircleOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(2.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);
  // задание линии OCCT
  Geom2d_Line aLineOCCT = Geom2d_Line(gp_Pnt2d(6.0, 0.0), gp_Dir2d(gp_Vec2d(0.0, 3.0)));

  Handle(Geom2d_Circle) aCircleOCCT1 = new Geom2d_Circle(aCircleOCCT);
  Handle(Geom2d_Line) aLine1 = new Geom2d_Line(aLineOCCT);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aCircleOCCT1, aLine1);

  std::shared_ptr<Curve> line = std::shared_ptr<Line>(new Line(6.0, 0.0, Vector(0.0, 3.0)));
  std::shared_ptr<Curve> circle = std::shared_ptr<Circle>(new Circle(2.0, 0.0, 3.0));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(line, circle);

  ASSERT_EQ(results->solution.size(), result.NbPoints());
}

// Точка, заданная по умолчанию
TEST(Line, SolutionForOCCT_7)
{
  // задание точки
  gp_Pnt2d aPointFirst;

  ASSERT_NEAR(aPointFirst.X(), 0.0, THE_TOLERANCE);
  ASSERT_NEAR(aPointFirst.Y(), 0.0, THE_TOLERANCE);
}

// Тест на соответствие точек в зависимоти от параметра
TEST(Circle, SolutionForOCCT_8)
{
  // задание окружности
  Geom2d_Circle aCircleOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(2.0, 1.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);

  gp_Pnt2d aPointFirst;
  aCircleOCCT.D0(2.0, aPointFirst);

  std::shared_ptr<Curve> circle = std::shared_ptr<Circle>(new Circle(2.0, 1.0, 3.0));

  ASSERT_NEAR(circle->PointCalcul(2).getX(), aPointFirst.X(), THE_TOLERANCE);
  ASSERT_NEAR(circle->PointCalcul(2).getY(), aPointFirst.Y(), THE_TOLERANCE);
}

// Две точки пересечения окружностей
TEST(CircleCircle, SolutionsForOCCT_9)
{

  Geom2d_Circle aCircleOCCT1 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 1.0);
  Geom2d_Circle aCircleOCCT2 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(1.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 1.0);

  Handle(Geom2d_Circle) aCircleOCCTNew1 = new Geom2d_Circle(aCircleOCCT1);
  Handle(Geom2d_Circle) aCircleOCCTNew2 = new Geom2d_Circle(aCircleOCCT2);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aCircleOCCTNew1, aCircleOCCTNew2);

  gp_Pnt2d rez1 = result.Point(1);
  gp_Pnt2d rez2 = result.Point(2);

  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(0.0, 0.0, 1.0));
  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(1.0, 0.0, 1.0));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(circle1, circle2);

  ASSERT_NEAR(results->solution[1].getX(), rez1.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[1].getY(), rez1.Y(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[0].getX(), rez2.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[0].getY(), rez2.Y(), THE_TOLERANCE);
}

// Пересечение окружности и прямой / сравнение решения (две точки)
TEST(LineCircle, SolutionsForOCCT_forCircleCircle)
{
  // задание окружности1 OCCT
  Geom2d_Circle aCircleOCCT1 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 1.0);
  // задание линии OCCT
  Geom2d_Line aLineOCCT = Geom2d_Line(gp_Pnt2d(0.5, 0.0), gp_Dir2d(gp_Vec2d(0.0, -1.0)));

  Handle(Geom2d_Circle) aCircleOCCT11 = new Geom2d_Circle(aCircleOCCT1);
  Handle(Geom2d_Line) aLine1 = new Geom2d_Line(aLineOCCT);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aCircleOCCT11, aLine1);

  gp_Pnt2d rez1 = result.Point(1);
  gp_Pnt2d rez2 = result.Point(2);

  // задание линии моего метода
  std::shared_ptr<Curve> line = std::shared_ptr<Line>(new Line(0.5, 0.0, Vector(0.0, -1.0)));
  // задание окружности моего метода
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(0.0, 0.0, 1.0));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(line, circle1);

  ASSERT_NEAR(results->solution[0].getX(), rez1.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[0].getY(), rez1.Y(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[1].getX(), rez2.X(), THE_TOLERANCE);
  ASSERT_NEAR(results->solution[1].getY(), rez2.Y(), THE_TOLERANCE);
}

// Одна точка пересечения окружностей
TEST(CircleCircle, SolutionForOCCT_10)
{
  Geom2d_Circle aCircleOCCT1 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(3.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);
  Geom2d_Circle aCircleOCCT2 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(9.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);

  Handle(Geom2d_Circle) aCircleOCCTNew1 = new Geom2d_Circle(aCircleOCCT1);
  Handle(Geom2d_Circle) aCircleOCCTNew2 = new Geom2d_Circle(aCircleOCCT2);


  Geom2dAPI_InterCurveCurve aResult(aCircleOCCTNew1, aCircleOCCTNew2);

  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(3.0, 0.0, 3.0));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(9.0, 0.0, 3.0));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(circle1, circle2);

  Standard_Integer aNbSegments = aResult.NbSegments();
  ASSERT_GE(aNbSegments, 2);

  aResult.Segment(1, aCircleOCCTNew1, aCircleOCCTNew2);

  Standard_Real aF1 = aCircleOCCTNew1->FirstParameter();
  Standard_Real aL1 = aCircleOCCTNew1->LastParameter();

  Standard_Real aF2 = aCircleOCCTNew2->FirstParameter();
  Standard_Real aL2 = aCircleOCCTNew2->LastParameter();

  Standard_Real aDifference1 = aL1 - aF1;
  Standard_Real aDifference2 = aL2 - aF2;

  Standard_Real aAverage1 = (aF1 + aL1)*0.5;
  Standard_Real aAverage2 = (aF2 + aL2)*0.5;

  aResult.Segment(2, aCircleOCCTNew1, aCircleOCCTNew2);

  Standard_Real aFF1 = aCircleOCCTNew1->FirstParameter();
  Standard_Real aLL1 = aCircleOCCTNew1->LastParameter();

  Standard_Real aFF2 = aCircleOCCTNew2->FirstParameter();
  Standard_Real aLL2 = aCircleOCCTNew2->LastParameter();

  Standard_Real aDifference11 = aLL1 - aFF1;
  Standard_Real aDifference22 = aLL2 - aFF2;

  Standard_Real aAverage11 = (aFF1 + aLL1)*0.5;
  Standard_Real aAverage22 = (aFF2 + aLL2)*0.5;
  // библиотека каскада не смогу найти точку пересечения двух окружностей (6,0)
  ASSERT_NE(results->solution[0].getX(), aAverage1);
  ASSERT_NE(results->solution[0].getY(), aAverage11);
  ASSERT_NEAR(aAverage1, 6.2828966323055999, THE_TOLERANCE);
  ASSERT_NEAR(aAverage2, 3.1418813285600047, THE_TOLERANCE);
  ASSERT_NEAR(aAverage11, 0.00028867487398587244, THE_TOLERANCE);
  ASSERT_NEAR(aAverage22, 3.1413039786195824, THE_TOLERANCE);
}

// Нет точек пересечения окружностей
TEST(CircleCircle, SolutionForOCCT_11)
{
  Geom2d_Circle aCircleOCCT1 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(3.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 2.0);
  Geom2d_Circle aCircleOCCT2 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(9.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);

  Handle(Geom2d_Circle) aCircleOCCTNew1 = new Geom2d_Circle(aCircleOCCT1);
  Handle(Geom2d_Circle) aCircleOCCTNew2 = new Geom2d_Circle(aCircleOCCT2);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  Geom2dAPI_InterCurveCurve result = Geom2dAPI_InterCurveCurve(aCircleOCCTNew1, aCircleOCCTNew2);

  std::shared_ptr<Curve> circle2 = std::shared_ptr<Circle>(new Circle(3.0, 0.0, 2.0));
  std::shared_ptr<Curve> circle1 = std::shared_ptr<Circle>(new Circle(9.0, 0.0, 3.0));

  Intersections intersection;
  std::shared_ptr<CalculationResult> results = intersection.Intersection(circle1, circle2);

  ASSERT_EQ(results->solution.size(), result.NbPoints());
}
