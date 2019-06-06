#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
// GoogleTest includes
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#include <gtest/gtest.h>
#include <Point.h>
#include <Line.h>
#include <cmath>
#include <Circle.h>
#include <Intersection.h>


#include <gp_Pnt2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2d_Circle.hxx>


static const double TOL = 1.e-7;


TEST(PointTest, Constructor)
{
    double x = 1.0, y = 2.0, z = 3.0;
    Point aPoint(x, y, z);
    
    ASSERT_NEAR(aPoint.X(), x, TOL);
    ASSERT_NEAR(aPoint.Y(), y, TOL);
    ASSERT_NEAR(aPoint.Z(), z, TOL);
}

TEST(PointTest, OperatorPlusVector)
{
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = -1.0, y2 = -5.0, z2 = 10.0;
    Point aPoint1 = Point(x1, y1, z1);
    Point aPoint2 = Point(x2, y2, z2);
    
    ASSERT_NEAR((aPoint1 + aPoint2).X(), x1 + x2, TOL);
    ASSERT_NEAR((aPoint1 + aPoint2).Y(), y1 + y2, TOL);
    ASSERT_NEAR((aPoint1 + aPoint2).Z(), z1 + z2, TOL);
    
    ASSERT_NEAR((aPoint2 + aPoint1).X(), x2 + x1, TOL);
    ASSERT_NEAR((aPoint2 + aPoint1).Y(), y2 + y1, TOL);
    ASSERT_NEAR((aPoint2 + aPoint1).Z(), z2 + z1, TOL);
    
    
}

TEST(PointTest, OperatorMul)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double t = 5;
    Point aPoint = Point(x, y, z);
    
    ASSERT_NEAR((aPoint * t).X(), x * t, TOL);
    ASSERT_NEAR((aPoint * t).Y(), y * t, TOL);
    ASSERT_NEAR((aPoint * t).Z(), z * t, TOL);
    
    
}

TEST(PointTest, OperatorSumScaler)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double t = 5;
    Point aPoint = Point(x, y, z);
    
    ASSERT_NEAR((aPoint + t).X(), x + t, TOL);
    ASSERT_NEAR((aPoint + t).Y(), y + t, TOL);
    ASSERT_NEAR((aPoint + t).Z(), z + t, TOL);
    
    
}

TEST(LineTest, LineValueTest)
{
    double x1 = 1.0, y1 = 2.0;
    double x2 = 3.0, y2 = 4.0;
    double t = 2.0;
    
    
    Point aPoint(x1, y1);
    Point aDirect(x2, y2);

    
    Line aLine(aPoint, aDirect);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(x1, y1);
    gp_Dir2d aDirCascade = gp_Dir2d(x2, y2);
    
    Geom2d_Line aLineCascade = Geom2d_Line(aPointCascade, aDirCascade);
    
    gp_Pnt2d anAns;
    
    aLineCascade.D0(t, anAns);
    
    Point aLineValue = aLine.Value(t);
    
    
    ASSERT_NEAR(aLineValue.X(), anAns.X(), TOL);
    ASSERT_NEAR(aLineValue.Y(), anAns.Y(), TOL);
    
}

TEST(LineTest, LineIsClosedTest)
{ // NOLINT(cert-err58-cpp)
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    
    Point aPoint(x1, y1, z1);
    Point aDirect(x2, y2, z2);
    
    Line aLine(aPoint, aDirect);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(1.0, 2.0);
    gp_Dir2d aDirCascade = gp_Dir2d(2.0, 3.0);
    
    Geom2d_Line aLineCascade = Geom2d_Line(aPointCascade, aDirCascade);
    
    ASSERT_EQ(aLine.IsClosed(), aLineCascade.IsClosed());
    
}

TEST(LineTest, LineTangent)
{
    double x1 = 1.0, y1 = 2.0;
    double x2 = 2.0, y2 = 3.0;
    double t = 2.0;
    
    
    Point aPoint(x1, y1);
    Point aDirect(x2, y2);
    
    Line aLine(aPoint, aDirect);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(x1, y1);
    gp_Dir2d aDirCascade = gp_Dir2d(x2, y2);
    
    Geom2d_Line aLineCascade = Geom2d_Line(aPointCascade, aDirCascade);
    
    gp_Pnt2d aPntAns;
    gp_Vec2d aVecAns = gp_Vec2d(aDirCascade);
    
    aLineCascade.D1(t, aPntAns, aVecAns);
    
    Point aLineTangent = aLine.Tangent(t);
    
    ASSERT_NEAR(aLineTangent.X(), aVecAns.X(), TOL);
    ASSERT_NEAR(aLineTangent.Y(), aVecAns.Y(), TOL);
    
}

TEST(CircleTest, CircleValueTest)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double aRadius = 5.0;
    double t = 2.0;
    
    Point aPoint(x, y, z);
    
    Circle aCircle(aPoint, aRadius);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(x, y);
    gp_Dir2d aDir = gp_Dir2d(1, 0);
    
    gp_Ax2d aXAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Geom2d_Circle aCircleCascade = Geom2d_Circle(aXAxis, aRadius);
    
    gp_Pnt2d aPntAns;
    
    aCircleCascade.D0(t, aPntAns);
    
    Point aCircleValue = aCircle.Value(t);
    
    
    ASSERT_NEAR(aCircleValue.X(), aPntAns.X(), TOL);
    ASSERT_NEAR(aCircleValue.Y(), aPntAns.Y(), TOL);
    
    
}

TEST(CircleTest, CircleIsClosedTest)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double aRadius = 5.0;
    Point aPoint1(x + 10, y - 13, z * 35);
    Point aPoint2(x - 25, y + 3, z - 7);
    Point aPoint3(x * 2, y / 3, z * 3);
    
    Circle aCircle1(aPoint1, aRadius);
    Circle aCircle2(aPoint2, aRadius + 7);
    Circle aCicle3(aPoint3, aRadius * 2);
    
    bool anAnswer = true;
    ASSERT_EQ(aCircle1.IsClosed(), anAnswer);
    ASSERT_EQ(aCircle2.IsClosed(), anAnswer);
    ASSERT_EQ(aCicle3.IsClosed(), anAnswer);
}


TEST(CircleTest, CircleTangent)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double aRadius = 5.0;
    double t = 2.0;
    
    
    Point aPoint(x, y, z);
    Circle aCircle(aPoint, aRadius);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(x, y);
    gp_Dir2d aDir = gp_Dir2d(1, 0);
    
    gp_Ax2d aXAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Geom2d_Circle aCircleCascade = Geom2d_Circle(aXAxis, aRadius);
    
    gp_Pnt2d aPntAns;
    gp_Vec2d aVecAns;
    
    aCircleCascade.D1(t, aPntAns, aVecAns);
    
    
    ASSERT_NEAR(aCircle.Tangent(t).X(), aVecAns.X(), TOL);
    ASSERT_NEAR(aCircle.Tangent(t).Y(), aVecAns.Y(), TOL);
    
}

TEST(IntersectionTest, LineLineIntersectPoint)
{
    Point aO = Point(3, 4, 5);
    Point aD = Point(1, 5, 8);
    Point aO1 = Point(4, 5, 6);
    Point aD1 = Point(2, 6, 9);
    
    
    shared_ptr<Line> aLine1(new Line(aO, aD));
    shared_ptr<Line> aLine2(new Line(aO1, aD1));
    
    Intersection aTestLine1 = Intersection(aLine1, aLine1);
    Intersection aTestLine2 = Intersection(aLine1, aLine2);
    
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 5.0);
    
    gp_Pnt2d aPoint2 = gp_Pnt2d(4.0, 5.0);
    gp_Dir2d aDirLine2 = gp_Dir2d(2.0, 6.0);
    
    Handle(Geom2d_Line) aLine3 = new Geom2d_Line(aPoint1, aDirLine1);
    Handle(Geom2d_Line) aLine4 = new Geom2d_Line(aPoint2, aDirLine2);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLine3, aLine4);
    
    gp_Pnt2d anAns = anInter.Point(1);
    
    ASSERT_NEAR(aTestLine2.FirstPoint().X(), anAns.X(), TOL);
    ASSERT_NEAR(aTestLine2.FirstPoint().Y(), anAns.Y(), TOL);
}


TEST(IntersectionTest, LineLineEquivalent)
{
    Point aO = Point(3, 4, 5);
    Point aD = Point(1, 5, 8);
    
    shared_ptr<Line> aLine(new Line(aO, aD));
    
    Intersection aTestLine = Intersection(aLine, aLine);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 5.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aLineCascade);
    
    
    ASSERT_EQ(aTestLine.CurrentStatus(), Intersection::EQUAL);
    
}

TEST(IntersectionTest, LineLineParallel)
{
    Point aO = Point(3, 4, 5);
    Point aD = Point(1, 5, 8);
    Point aO1 = Point(4, 5, 6);
    
    
    shared_ptr<Line> aLine(new Line(aO, aD));
    shared_ptr<Line> aLine2(new Line(aO1, aD));
    
    Intersection aTestLine = Intersection(aLine, aLine2);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 5.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aLineCascade);
    
    
    ASSERT_EQ(aTestLine.NumberInter(), anInter.NbPoints());
    
}

TEST(IntersectionTest, LineCirclePoints1)
{
    Point aO = Point(0, 0, 0);
    Point aD = Point(1, 0, 0);
    Point aCenter = Point(0, 0, 0);
    
    double aRadius = 5;
    
    shared_ptr<Line> aLine1(new Line(aO, aD));
    shared_ptr<Circle> aCircle1(new Circle(aCenter, aRadius));
    
    Intersection aTestLine1 = Intersection(aLine1, aCircle1);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(0.0, 0.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 0.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(0.0, 0.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Ax2d aXAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade = new Geom2d_Circle(aXAxis, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aCircleCascade);
    
    gp_Pnt2d anAns1 = anInter.Point(1);
    gp_Pnt2d anAns2 = anInter.Point(2);
    
    ASSERT_NEAR(aTestLine1.FirstPoint().X(), anAns2.X(), TOL);
    ASSERT_NEAR(aTestLine1.FirstPoint().Y(), anAns2.Y(), TOL);
    ASSERT_NEAR(aTestLine1.SecondPoint().X(), anAns1.X(), TOL);
    ASSERT_NEAR(aTestLine1.SecondPoint().Y(), anAns1.Y(), TOL);
    
    
}

TEST(IntersectionTest, LineCirclePoints2)
{
    Point aO = Point(0, 0, 0);
    Point aD = Point(1, 0, 0);
    Point aCenter = Point(0, 5, 0);
    double aRadius = 5;
    
    shared_ptr<Line> aLine1(new Line(aO, aD));
    shared_ptr<Circle> aCircle2(new Circle(aCenter, aRadius));
    
    Intersection aTestLine = Intersection(aLine1, aCircle2);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(0.0, 0.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 0.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(0.0, 5.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Ax2d aXAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade = new Geom2d_Circle(aXAxis, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aCircleCascade);
    
    gp_Pnt2d anAns1 = anInter.Point(1);
    
    
    ASSERT_NEAR(fabs(aTestLine.FirstPoint().X()), anAns1.X(), TOL);
    ASSERT_NEAR(fabs(aTestLine.FirstPoint().Y()), anAns1.Y(), TOL);
    
    
}

TEST(IntersectionTest, LineCirclePoints)
{
    Point aO = Point(2, 0, 0);
    Point aD = Point(5, -3, 0);
    Point aCenter = Point(1, 1, 0);
    
    double aRadius = 1;
    
    shared_ptr<Line> aLine1(new Line(aO, aD));
    shared_ptr<Circle> aCircle1(new Circle(aCenter, aRadius));
    
    Intersection aTestLine1 = Intersection(aLine1, aCircle1);
    
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(2.0, 0.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(5.0, -3.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(1.0, 1.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Ax2d aXAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade = new Geom2d_Circle(aXAxis, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aCircleCascade);
    
    gp_Pnt2d anAns1 = anInter.Point(1);
    gp_Pnt2d anAns2 = anInter.Point(2);
    
    ASSERT_NEAR(aTestLine1.FirstPoint().X(), anAns2.X(), TOL);
    ASSERT_NEAR(aTestLine1.FirstPoint().Y(), anAns2.Y(), TOL);
    ASSERT_NEAR(aTestLine1.SecondPoint().X(), anAns1.X(), TOL);
    ASSERT_NEAR(aTestLine1.SecondPoint().Y(), anAns1.Y(), TOL);
    
    
}


TEST(IntersectionTest, LineCircleNotInter)
{
    Point aO = Point(3, 4, 5);
    Point aD = Point(1, 5, 8);
    Point aO1 = Point(100, 200, -100);
    double aRadius = 5;
    
    shared_ptr<Line> aLine(new Line(aO, aD));
    shared_ptr<Circle> aCircle(new Circle(aO1, aRadius));
    
    Intersection aTestLine = Intersection(aLine, aCircle);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 5.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(100.0, 200.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Ax2d aXAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade = new Geom2d_Circle(aXAxis, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aCircleCascade);
    
    ASSERT_EQ(aTestLine.NumberInter(), anInter.NbPoints());
    
}

TEST(IntersectionTest, CircleLineIntersect)
{
    Point aO = Point(3, 4, 5);
    Point aD = Point(1, 5, 8);
    Point aO1 = Point(100, 200, -100);
    double aRadius = 5;
    
    shared_ptr<Line> aLine(new Line(aO, aD));
    shared_ptr<Circle> aCircle(new Circle(aO1, aRadius));
    
    Intersection aTestLine = Intersection(aCircle, aLine);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 5.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(100.0, 200.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Ax2d aXAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade = new Geom2d_Circle(aXAxis, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aCircleCascade, aLineCascade);
    
    ASSERT_EQ(aTestLine.NumberInter(), anInter.NbPoints());
    
}


TEST(IntersectionTest, CircleCirclePoints2)
{
    Point aCenter = Point(0, 0, 0);
    Point aCenter2 = Point(1, 7, 1);
    double aRadius = 5;
    
    shared_ptr<Circle> aCircle1(new Circle(aCenter, aRadius));
    shared_ptr<Circle> aCircle3(new Circle(aCenter2, aRadius));
    
    Intersection aTestLine = Intersection(aCircle1, aCircle3);
    
    gp_Pnt2d aPointCascade1 = gp_Pnt2d(0.0, 0.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Pnt2d aPointCascade2 = gp_Pnt2d(1.0, 7.0);
    
    gp_Ax2d aXAxis1 = gp_Ax2d(aPointCascade1, aDir);
    gp_Ax2d aXAxis2 = gp_Ax2d(aPointCascade2, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade1 = new Geom2d_Circle(aXAxis1, aRadius);
    Handle(Geom2d_Circle) aCircleCascade2 = new Geom2d_Circle(aXAxis2, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aCircleCascade1, aCircleCascade2);
    
    gp_Pnt2d anAns1 = anInter.Point(1);
    gp_Pnt2d anAns2 = anInter.Point(2);
    
    
    ASSERT_NEAR(aTestLine.FirstPoint().X(), anAns1.X(), TOL);
    ASSERT_NEAR(aTestLine.FirstPoint().Y(), anAns1.Y(), TOL);
    ASSERT_NEAR(aTestLine.SecondPoint().X(), anAns2.X(), TOL);
    ASSERT_NEAR(aTestLine.SecondPoint().Y(), anAns2.Y(), TOL);
}

TEST(IntersectionTest, CircleCircleEqual)
{
    Point aO = Point(3, 4, 5);
    double aRadius = 5.0;
    
    
    shared_ptr<Circle> aCircle(new Circle(aO, aRadius));
    
    Intersection aTestLine = Intersection(aCircle, aCircle);
    
    ASSERT_EQ(aTestLine.CurrentStatus(), Intersection::EQUAL);
    
}

TEST(IntersectionTest, CircleCircleNotInter)
{
    Point aO = Point(3, 4, 5);
    Point aO1 = Point(20, 30, 40);
    double aRadius = 5.0;
    double aRadius1 = 1.0;
    
    
    shared_ptr<Circle> aCircle(new Circle(aO, aRadius));
    shared_ptr<Circle> aCircle1(new Circle(aO1, aRadius1));
    
    Intersection aTestLine = Intersection(aCircle, aCircle1);
    
    gp_Pnt2d aPointCascade1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Pnt2d aPointCascade2 = gp_Pnt2d(5.0, 1.0);
    
    gp_Ax2d aXAxis1 = gp_Ax2d(aPointCascade1, aDir);
    gp_Ax2d aXAxis2 = gp_Ax2d(aPointCascade2, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade1 = new Geom2d_Circle(aXAxis1, aRadius);
    Handle(Geom2d_Circle) aCircleCascade2 = new Geom2d_Circle(aXAxis2, aRadius1);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aCircleCascade1, aCircleCascade2);
    
    
    ASSERT_EQ(aTestLine.NumberInter(), anInter.NbPoints());
    
}


//=============================================================================
//function : main
//purpose  :
//=============================================================================
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#pragma clang diagnostic pop
