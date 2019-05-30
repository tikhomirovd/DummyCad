#include <gtest/gtest.h>

// Includes from Core.

#include <memory>


#include <Geom2d_Line.hxx>
#include <Geom2d_Point.hxx>
#include <Geom2d_Vector.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Geometry.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

static const double THE_TOLERANCE = 1.e-7;

TEST(Line, SolutionForOCCT)
{
  // задание точки
  gp_Pnt2d aPointFirst = gp_Pnt2d(0.0,0.0);
  // задание вектора
  gp_Dir2d aVectorFirst = gp_Dir2d(gp_Vec2d(1.0,0.0));
  // задание точки
  gp_Pnt2d aPointSecond = gp_Pnt2d(0.0, 0.0);
  // задание вектора
  gp_Dir2d aVectorSecond = gp_Dir2d(gp_Vec2d(0.0, 1.0));
  // задание линии
  Geom2d_Line aLineFirst = Geom2d_Line(aPointFirst, aVectorFirst);
  Geom2d_Line aLineSecond = Geom2d_Line(aPointSecond, aVectorSecond);

  Geom2dAPI_InterCurveCurve aGeom2dAPI_InterCurveCurve;

  ASSERT_NEAR(aPointFirst.X(), 0.0, THE_TOLERANCE);
  ASSERT_NEAR(aPointFirst.Y(), 0.0, THE_TOLERANCE);
}