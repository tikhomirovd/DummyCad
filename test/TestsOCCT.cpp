// GoogleTest includes
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#include <gtest/gtest.h>

// Includes from STL.
#include <memory>

// Includes from Core.
#include <Circle.h>
#include <Intersection.h>
#include <Curve.h>
#include <Line.h>

// Includes from Cascade.
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

static const double THE_TOLERANCE = 1.e-7;

// Метод пересечения двух линий и сравнение полученных решений (одна точка пересечения)
TEST(LineLine, OneSolutionForOCCT_01)
{
  // задание линии1 OCCT
  Geom2d_Line aLineFirst = Geom2d_Line(gp_Pnt2d(0.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0)));
  // задание линии2 OCCT
  Geom2d_Line aLineSecond = Geom2d_Line(gp_Pnt2d(0.0, 0.0), gp_Dir2d(gp_Vec2d(0.0, 1.0)));

  Handle(Geom2d_Line) aLine1 = new Geom2d_Line(aLineFirst);
  Handle(Geom2d_Line) aLine2 = new Geom2d_Line(aLineSecond);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult = Geom2dAPI_InterCurveCurve(aLine1, aLine2);

  // берем результат по индексу
  gp_Pnt2d aRez = aResult.Point(1);

  // задание линий моего метода
  std::shared_ptr<Curve> LineOne = std::shared_ptr<Line>(new Line(0.0, 0.0, Vector(1.0, 0.0)));
  std::shared_ptr<Curve> LineTwo = std::shared_ptr<Line>(new Line(0.0, 0.0, Vector(0.0, 1.0)));

  // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Result = intersection.Intersection(LineOne, LineTwo);

  ASSERT_NEAR(Result->solution[0].getX(), aRez.X(), THE_TOLERANCE);
  ASSERT_NEAR(Result->solution[0].getY(), aRez.Y(), THE_TOLERANCE);
}

// Нет пересечения двух линий / сравнение решения
TEST(LineLine, NoSolutionForOCCT_02)
{
  // задание линии1 OCCT
  Geom2d_Line aLineFirst = Geom2d_Line(gp_Pnt2d(0.0, 5.0), gp_Dir2d(gp_Vec2d(1.0, 0.0)));
  // задание линии2 OCCT
  Geom2d_Line aLineSecond = Geom2d_Line(gp_Pnt2d(0.0, 3.0), gp_Dir2d(gp_Vec2d(1.0, 0.0)));

  Handle(Geom2d_Line) aLine1 = new Geom2d_Line(aLineFirst);
  Handle(Geom2d_Line) aLine2 = new Geom2d_Line(aLineSecond);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult = Geom2dAPI_InterCurveCurve(aLine1, aLine2);

  // задание линий моего метода
  std::shared_ptr<Curve> LineOne = std::shared_ptr<Line>(new Line(0.0, 5.0, Vector(1.0, 0.0)));
  std::shared_ptr<Curve> LineTwo = std::shared_ptr<Line>(new Line(0.0, 3.0, Vector(1.0, 0.0)));

  // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Result = intersection.Intersection(LineOne, LineTwo);

  ASSERT_EQ(Result->solution.size(), aResult.NbPoints());
}

// Линии совпадают / сравнение решения
TEST(LineLine, CoincidenceSolutionForOCCT_03)
{
  // задание линии1 OCCT
  Geom2d_Line aLineFirst = Geom2d_Line(gp_Pnt2d(0.0, 5.0), gp_Dir2d(gp_Vec2d(1.0, 0.0)));
  // задание линии2 OCCT
  Geom2d_Line aLineSecond = Geom2d_Line(gp_Pnt2d(0.0, 5.0), gp_Dir2d(gp_Vec2d(1.0, 0.0)));

  Handle(Geom2d_Line) aLine1 = new Geom2d_Line(aLineFirst);
  Handle(Geom2d_Line) aLine2 = new Geom2d_Line(aLineSecond);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult = Geom2dAPI_InterCurveCurve(aLine1, aLine2);

  // задание линий моего метода
  std::shared_ptr<Curve> LineOne = std::shared_ptr<Line>(new Line(0.0, 5.0, Vector(1.0, 0.0)));
  std::shared_ptr<Curve> LineTwo = std::shared_ptr<Line>(new Line(0.0, 5.0, Vector(1.0, 0.0)));

  // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Result = intersection.Intersection(LineOne, LineTwo);

  ASSERT_EQ(Result->solution.size(), aResult.NbPoints());
}

// Точка, заданная по умолчанию
TEST(Line, ParameterSolutionForOCCT_04)
{
  // задание точки
  gp_Pnt2d aPointFirst;

  ASSERT_NEAR(aPointFirst.X(), 0.0, THE_TOLERANCE);
  ASSERT_NEAR(aPointFirst.Y(), 0.0, THE_TOLERANCE);
}

// Пересечение окружности и прямой / сравнение решения (две точки)
TEST(LineCircle, TwoSolutionsForOCCT_05)
{
  // задание окружности OCCT
  Geom2d_Circle aCircleOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(2.0, 1.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);
  // задание линии OCCT
  Geom2d_Line aLineOCCT = Geom2d_Line(gp_Pnt2d(2.0, 0.0), gp_Dir2d(gp_Vec2d(0.0, 2.0)));

  Handle(Geom2d_Circle) aCircleForOCCT = new Geom2d_Circle(aCircleOCCT);
  Handle(Geom2d_Line) aLineForOCCT = new Geom2d_Line(aLineOCCT);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult = Geom2dAPI_InterCurveCurve(aCircleForOCCT, aLineForOCCT);

  // берем результаты по индексам
  gp_Pnt2d aRez1 = aResult.Point(1);
  gp_Pnt2d aRez2 = aResult.Point(2);

  // задание линии моего метода
  std::shared_ptr<Curve> myLine = std::shared_ptr<Line>(new Line(2.0, 0.0, Vector(0.0, 2.0)));
  // задание окружности моего метода
  std::shared_ptr<Curve> myCircle = std::shared_ptr<Circle>(new Circle(2.0, 1.0, 3.0));

  // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Results = intersection.Intersection(myLine, myCircle);

  ASSERT_NEAR(Results->solution[1].getX(), aRez1.X(), THE_TOLERANCE);
  ASSERT_NEAR(Results->solution[1].getY(), aRez1.Y(), THE_TOLERANCE);
  ASSERT_NEAR(Results->solution[0].getX(), aRez2.X(), THE_TOLERANCE);
  ASSERT_NEAR(Results->solution[0].getY(), aRez2.Y(), THE_TOLERANCE);
}

// Пересечение окружности и прямой / сравнение решения (одна точка)
TEST(LineCircle, OneSolutionForOCCT_06)
{
  // задание окружности OCCT
  Geom2d_Circle aCircleOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(2.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);
  // задание линии OCCT
  Geom2d_Line aLineOCCT = Geom2d_Line(gp_Pnt2d(0.0, 3.0), gp_Dir2d(gp_Vec2d(5.0, 0.0)));

  Handle(Geom2d_Circle) aCircleForOCCT = new Geom2d_Circle(aCircleOCCT);
  Handle(Geom2d_Line) aLineForOCCT = new Geom2d_Line(aLineOCCT);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult = Geom2dAPI_InterCurveCurve(aCircleForOCCT, aLineForOCCT);

  // берем результат по индексу
  gp_Pnt2d aRez = aResult.Point(1);

  // задание линии моего метода
  std::shared_ptr<Curve> myLine = std::shared_ptr<Line>(new Line(0.0, 3.0, Vector(5.0, 0.0)));
  // задание окружности моего метода
  std::shared_ptr<Curve> myCircle = std::shared_ptr<Circle>(new Circle(2.0, 0.0, 3.0));

  // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Result = intersection.Intersection(myLine, myCircle);

  ASSERT_NEAR(Result->solution[0].getX(), aRez.X(), THE_TOLERANCE);
  ASSERT_NEAR(Result->solution[0].getY(), aRez.Y(), THE_TOLERANCE);
}

// Нет пересечения окружности и прямой / сравнение решения
TEST(LineCircle, NoSolutionForOCCT_07)
{
  // задание окружности OCCT
  Geom2d_Circle aCircleOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(2.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);
  // задание линии OCCT
  Geom2d_Line aLineOCCT = Geom2d_Line(gp_Pnt2d(6.0, 0.0), gp_Dir2d(gp_Vec2d(0.0, 3.0)));

  Handle(Geom2d_Circle) aCircleForOCCT = new Geom2d_Circle(aCircleOCCT);
  Handle(Geom2d_Line) aLineForOCCT = new Geom2d_Line(aLineOCCT);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult = Geom2dAPI_InterCurveCurve(aCircleForOCCT, aLineForOCCT);

  // задание линии моего метода
  std::shared_ptr<Curve> myLine = std::shared_ptr<Line>(new Line(6.0, 0.0, Vector(0.0, 3.0)));
  // задание окружности моего метода
  std::shared_ptr<Curve> myCircle = std::shared_ptr<Circle>(new Circle(2.0, 0.0, 3.0));

  // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Result = intersection.Intersection(myLine, myCircle);

  ASSERT_EQ(Result->solution.size(), aResult.NbPoints());
}

// Пересечение окружности и прямой / сравнение решения (две точки)
TEST(LineCircle, TwoSolutionsForOCCT_08)
{
  // задание окружности OCCT
  Geom2d_Circle aCircleOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 1.0);
  // задание линии OCCT
  Geom2d_Line aLineOCCT = Geom2d_Line(gp_Pnt2d(0.5, 0.0), gp_Dir2d(gp_Vec2d(0.0, -1.0)));

  Handle(Geom2d_Circle) aCircleForOCCT = new Geom2d_Circle(aCircleOCCT);
  Handle(Geom2d_Line) aLineForOCCT = new Geom2d_Line(aLineOCCT);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult = Geom2dAPI_InterCurveCurve(aCircleForOCCT, aLineForOCCT);

  // берем результаты по индексу
  gp_Pnt2d aRezOne = aResult.Point(1);
  gp_Pnt2d aRezTwo = aResult.Point(2);

  // задание линии моего метода
  std::shared_ptr<Curve> myLine = std::shared_ptr<Line>(new Line(0.5, 0.0, Vector(0.0, -1.0)));
  // задание окружности моего метода
  std::shared_ptr<Curve> myCircle = std::shared_ptr<Circle>(new Circle(0.0, 0.0, 1.0));

  // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Results = intersection.Intersection(myLine, myCircle);

  ASSERT_NEAR(Results->solution[0].getX(), aRezOne.X(), THE_TOLERANCE);
  ASSERT_NEAR(Results->solution[0].getY(), aRezOne.Y(), THE_TOLERANCE);
  ASSERT_NEAR(Results->solution[1].getX(), aRezTwo.X(), THE_TOLERANCE);
  ASSERT_NEAR(Results->solution[1].getY(), aRezTwo.Y(), THE_TOLERANCE);
}

// Тест на соответствие точек в зависимоти от заданного параметра
TEST(Circle, ParameterSolutionForOCCT_09)
{
  // задание окружности
  Geom2d_Circle aCircleOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(2.0, 1.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);

  // задание точки, в которой будет хранится результат
  gp_Pnt2d aPointFirst;
  // вычисление точки в зависимости от переданного параметра
  aCircleOCCT.D0(2.0, aPointFirst);

  // задание окружности моего метода
  std::shared_ptr<Curve> myCircle = std::shared_ptr<Circle>(new Circle(2.0, 1.0, 3.0));

  ASSERT_NEAR(myCircle->PointCalcul(2).getX(), aPointFirst.X(), THE_TOLERANCE);
  ASSERT_NEAR(myCircle->PointCalcul(2).getY(), aPointFirst.Y(), THE_TOLERANCE);
}

// Две точки пересечения окружностей
TEST(CircleCircle, TwoSolutionsForOCCT_10)
{
  // задание окружности1
  Geom2d_Circle aCircleOCCT1 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 1.0);
  // задание окружности2
  Geom2d_Circle aCircleOCCT2 = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(1.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 1.0);

  Handle(Geom2d_Circle) aCircleOneForOCCT = new Geom2d_Circle(aCircleOCCT1);
  Handle(Geom2d_Circle) aCircleTwoForOCCT = new Geom2d_Circle(aCircleOCCT2);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult = Geom2dAPI_InterCurveCurve(aCircleOneForOCCT, aCircleTwoForOCCT);

  // берем результаты по индексу
  gp_Pnt2d aRezOne = aResult.Point(1);
  gp_Pnt2d aRezTwo = aResult.Point(2);

  // задание окружности1 моего метода
  std::shared_ptr<Curve> CircleOne = std::shared_ptr<Circle>(new Circle(0.0, 0.0, 1.0));
  // задание окружности2 моего метода
  std::shared_ptr<Curve> CircleTwo = std::shared_ptr<Circle>(new Circle(1.0, 0.0, 1.0));

   // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Results = intersection.Intersection(CircleOne, CircleTwo);

  ASSERT_NEAR(Results->solution[1].getX(), aRezOne.X(), THE_TOLERANCE);
  ASSERT_NEAR(Results->solution[1].getY(), aRezOne.Y(), THE_TOLERANCE);
  ASSERT_NEAR(Results->solution[0].getX(), aRezTwo.X(), THE_TOLERANCE);
  ASSERT_NEAR(Results->solution[0].getY(), aRezTwo.Y(), THE_TOLERANCE);
}

// Одна точка пересечения окружностей
TEST(CircleCircle, OneSolutionForOCCT_11)
{
  // задание окружности1 OCCT
  Geom2d_Circle aCircleOneOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(3.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);
  // задание окружности2 OCCT
  Geom2d_Circle aCircleTwoOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(9.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);

  Handle(Geom2d_Circle) aCircleOneForOCCT = new Geom2d_Circle(aCircleOneOCCT);
  Handle(Geom2d_Circle) aCircleTwoForOCCT = new Geom2d_Circle(aCircleTwoOCCT);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult(aCircleOneForOCCT, aCircleTwoForOCCT);

  // задание окружности2 моего метода
  std::shared_ptr<Curve> CircleTwo = std::shared_ptr<Circle>(new Circle(3.0, 0.0, 3.0));
  // задание окружности1 моего метода
  std::shared_ptr<Curve> CircleOne = std::shared_ptr<Circle>(new Circle(9.0, 0.0, 3.0));

  // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Result = intersection.Intersection(CircleOne, CircleTwo);

  // получаем колличество сегментов, которые находит библиотека каскада
  Standard_Integer aNbSegments = aResult.NbSegments();
  ASSERT_GE(aNbSegments, 2);

  // получаем результаты первого сегмента
  aResult.Segment(1, aCircleOneForOCCT, aCircleTwoForOCCT);

  // получение параметров с первой окружности
  Standard_Real aFOne = aCircleOneForOCCT->FirstParameter();
  Standard_Real aLOne = aCircleOneForOCCT->LastParameter();

  // получение параметров со второй окружности
  Standard_Real aFTwo = aCircleTwoForOCCT->FirstParameter();
  Standard_Real aLTwo = aCircleTwoForOCCT->LastParameter();

  // получаем разность координат
  Standard_Real aDifferenceOne = aLOne - aFOne;
  Standard_Real aDifferenceTwo = aLTwo - aFTwo;

  // усредняем значение параметров
  Standard_Real aAverageOne = (aFOne + aLOne)*0.5;
  Standard_Real aAverageTwo = (aFTwo + aLTwo)*0.5;

  // получаем результаты второго сегмента
  aResult.Segment(2, aCircleOneForOCCT, aCircleTwoForOCCT);

  // получение параметров с первой окружности
  Standard_Real aFFOne = aCircleOneForOCCT->FirstParameter();
  Standard_Real aLLOne = aCircleOneForOCCT->LastParameter();

  // получение параметров со второй окружности
  Standard_Real aFFTwo = aCircleTwoForOCCT->FirstParameter();
  Standard_Real aLLTwo = aCircleTwoForOCCT->LastParameter();

  // получаем разность координат
  Standard_Real aDifferenceOneOne = aLLOne - aFFOne;
  Standard_Real aDifferenceTwoTwo = aLLTwo - aFFTwo;

  // усредняем значение параметров
  Standard_Real aAverageOneOne = (aFFOne + aLLOne)*0.5;
  Standard_Real aAverageTwoTwo = (aFFTwo + aLLTwo)*0.5;

  // библиотека каскада не смогла найти точку пересечения двух окружностей (6,0)
  // возвращается сегмент с неточными точками

  // доказываем несоответствие результатов моего метода и решения библиотека каскада
  ASSERT_NE(Result->solution[0].getX(), aAverageOne);
  ASSERT_NE(Result->solution[0].getY(), aAverageOneOne);

  ASSERT_NEAR(aAverageOne, 6.2828966323055999, THE_TOLERANCE);
  ASSERT_NEAR(aAverageTwo, 3.1418813285600047, THE_TOLERANCE);
  ASSERT_NEAR(aAverageOneOne, 0.00028867487398587244, THE_TOLERANCE);
  ASSERT_NEAR(aAverageTwoTwo, 3.1413039786195824, THE_TOLERANCE);
}

// Нет точек пересечения окружностей
TEST(CircleCircle, NoSolutionForOCCT_12)
{
  // задание окружности1 OCCT
  Geom2d_Circle aCircleOneOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(3.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 2.0);
  // задание окружности2 OCCT
  Geom2d_Circle aCircleTwoOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(9.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.0);

  Handle(Geom2d_Circle) aCircleOneForOCCT = new Geom2d_Circle(aCircleOneOCCT);
  Handle(Geom2d_Circle) aCircleTwoForOCCT = new Geom2d_Circle(aCircleTwoOCCT);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult = Geom2dAPI_InterCurveCurve(aCircleOneForOCCT, aCircleTwoForOCCT);

  // задание окружности2 моего метода
  std::shared_ptr<Curve> CircleTwo = std::shared_ptr<Circle>(new Circle(3.0, 0.0, 2.0));
  // задание окружности1 моего метода
  std::shared_ptr<Curve> CircleOne = std::shared_ptr<Circle>(new Circle(9.0, 0.0, 3.0));

  // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Result = intersection.Intersection(CircleOne, CircleTwo);

  ASSERT_EQ(Result->solution.size(), aResult.NbPoints());
}

// Одна точка пересечения окружностей с нецелочисленными радиусами
TEST(CircleCircle, OneSolutionForOCCT_13)
{
  // задание окружности1 OCCT
  Geom2d_Circle aCircleOneOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(3.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 3.5);
  // задание окружности2 OCCT
  Geom2d_Circle aCircleTwoOCCT = Geom2d_Circle(gp_Ax2d(gp_Pnt2d(9.0, 0.0), gp_Dir2d(gp_Vec2d(1.0, 0.0))), 2.5);

  Handle(Geom2d_Circle) aCircleOneForOCCT = new Geom2d_Circle(aCircleOneOCCT);
  Handle(Geom2d_Circle) aCircleTwoForOCCT = new Geom2d_Circle(aCircleTwoOCCT);

  // обращаемся к методу пересечения
  Geom2dAPI_InterCurveCurve aResult = Geom2dAPI_InterCurveCurve(aCircleOneForOCCT, aCircleTwoForOCCT);

  // получаем колличество сегментов, которые находит библиотека каскада
  Standard_Integer aNbSegments = aResult.NbSegments();
  ASSERT_GE(aNbSegments, 2);

  // получение параметров с первой окружности
  Standard_Real aFOne = aCircleOneForOCCT->FirstParameter();
  Standard_Real aLOne = aCircleOneForOCCT->LastParameter();

  // получение параметров со второй окружности
  Standard_Real aFTwo = aCircleTwoForOCCT->FirstParameter();
  Standard_Real aLTwo = aCircleTwoForOCCT->LastParameter();

  // получаем разность координат
  Standard_Real aDifferenceOne = aLOne - aFOne;
  Standard_Real aDifferenceTwo = aLTwo - aFTwo;

  // усредняем значение параметров
  Standard_Real aAverageOne = (aFOne + aLOne)*0.5;
  Standard_Real aAverageTwo = (aFTwo + aLTwo)*0.5;

  // получаем результаты второго сегмента
  aResult.Segment(2, aCircleOneForOCCT, aCircleTwoForOCCT);

  // получение параметров с первой окружности
  Standard_Real aFFOne = aCircleOneForOCCT->FirstParameter();
  Standard_Real aLLOne = aCircleOneForOCCT->LastParameter();

  // получение параметров со второй окружности
  Standard_Real aFFTwo = aCircleTwoForOCCT->FirstParameter();
  Standard_Real aLLTwo = aCircleTwoForOCCT->LastParameter();

  // получаем разность координат
  Standard_Real aDifferenceOneOne = aLLOne - aFFOne;
  Standard_Real aDifferenceTwoTwo = aLLTwo - aFFTwo;

  // усредняем значение параметров
  Standard_Real aAverageOneOne = (aFFOne + aLLOne)*0.5;
  Standard_Real aAverageTwoTwo = (aFFTwo + aLLTwo)*0.5;

  // библиотека каскада не смогла найти точку пересечения двух окружностей (6.5,0)
  // возвращается сегмент с неточными точками

  // задание окружности2 моего метода
  std::shared_ptr<Curve> CircleTwo = std::shared_ptr<Circle>(new Circle(3.0, 0.0, 3.5));
  // задание окружности1 моего метода
  std::shared_ptr<Curve> CircleOne = std::shared_ptr<Circle>(new Circle(9.0, 0.0, 2.5));

  // обращаемся к методу пересечения
  Intersections intersection;
  std::shared_ptr<CalculationResult> Result = intersection.Intersection(CircleOne, CircleTwo);

  ASSERT_NE(Result->solution[0].getX(), aAverageOne);
  ASSERT_NE(Result->solution[0].getY(), aAverageOneOne);
}