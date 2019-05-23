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
    Point point(x, y, z);
    
    ASSERT_NEAR(point.X(), x, TOL);
    ASSERT_NEAR(point.Y(), y, TOL);
    ASSERT_NEAR(point.Z(), z, TOL);
}

TEST(PointTest, OperatorPlusVector)
{
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = -1.0, y2 = -5.0, z2 = 10.0;
    Point point1 = Point(x1, y1, z1);
    Point point2 = Point(x2, y2, z2);
    
    ASSERT_NEAR((point1 + point2).X(), x1 + x2, TOL);
    ASSERT_NEAR((point1 + point2).Y(), y1 + y2, TOL);
    ASSERT_NEAR((point1 + point2).Z(), z1 + z2, TOL);
    
    ASSERT_NEAR((point2 + point1).X(), x2 + x1, TOL);
    ASSERT_NEAR((point2 + point1).Y(), y2 + y1, TOL);
    ASSERT_NEAR((point2 + point1).Z(), z2 + z1, TOL);
    
    
}

TEST(PointTest, OperatorMul)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double t = 5;
    Point point = Point(x, y, z);
    
    ASSERT_NEAR((point * t).X(), x * t, TOL);
    ASSERT_NEAR((point * t).Y(), y * t, TOL);
    ASSERT_NEAR((point * t).Z(), z * t, TOL);
    
    
}

TEST(PointTest, OperatorSumScaler)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double t = 5;
    Point point = Point(x, y, z);
    
    ASSERT_NEAR((point + t).X(), x + t, TOL);
    ASSERT_NEAR((point + t).Y(), y + t, TOL);
    ASSERT_NEAR((point + t).Z(), z + t, TOL);
    
    
}

TEST(LineTest, LineValueTest)
{
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 3.0, y2 = 4.0, z2 = 3.0;
    double t = 2.0;
    
    
    Point aPoint(x1, y1, z1);
    Point aDirect(x2, y2, z2);
    aDirect.Norm();
    
    Line line(aPoint, aDirect);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(x1, y1);
    gp_Dir2d aDirCascade = gp_Dir2d(x2, y2);
    
    Geom2d_Line aLineCascade = Geom2d_Line(aPointCascade, aDirCascade);
    
    gp_Pnt2d ans;
    
    aLineCascade.D0(t, ans);
    
    
    ASSERT_NEAR(line.Value(t).X(), ans.X(), TOL);
    ASSERT_NEAR(line.Value(t).Y(), ans.Y(), TOL);
    
}

TEST(LineTest, LineIsClosedTest)
{ // NOLINT(cert-err58-cpp)
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    
    Point point(x1, y1, z1);
    Point direct(x2, y2, z2);
    
    Line line(point, direct);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(1.0, 2.0);
    gp_Dir2d aDirCascade = gp_Dir2d(2.0, 3.0);
    
    Geom2d_Line aLineCascade = Geom2d_Line(aPointCascade, aDirCascade);
    
    ASSERT_EQ(line.IsClosed(), aLineCascade.IsClosed());
    
}

TEST(LineTest, LineTangent)
{
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    double t = 2.0;
    
    
    Point point(x1, y1, z1);
    Point direct(x2, y2, z2);
    direct.Norm();
    
    Line line(point, direct);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(x1, y1);
    gp_Dir2d aDirCascade = gp_Dir2d(x2, y2);
    
    Geom2d_Line aLineCascade = Geom2d_Line(aPointCascade, aDirCascade);
    
    gp_Pnt2d aPntAns;
    gp_Vec2d aVecAns = gp_Vec2d(aDirCascade);
    
    aLineCascade.D1(t, aPntAns, aVecAns);
    
    ASSERT_NEAR(line.Tangent(t).X(), aVecAns.X(), TOL);
    ASSERT_NEAR(line.Tangent(t).Y(), aVecAns.Y(), TOL);
    
}

TEST(CircleTest, CircleValueTest)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double aRadius = 5.0;
    double t = 2.0;
    
    Point point(x, y, z);
    
    Circle circle(point, aRadius);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(x, y);
    gp_Dir2d aDir = gp_Dir2d(1, 0);
    
    gp_Ax2d XAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Geom2d_Circle aCircleCascade = Geom2d_Circle(XAxis, aRadius);
    
    gp_Pnt2d aPntAns;
    
    aCircleCascade.D0(t, aPntAns);
    
    
    ASSERT_NEAR(circle.Value(t).X(), aPntAns.X(), TOL);
    ASSERT_NEAR(circle.Value(t).Y(), aPntAns.Y(), TOL);
    
    
}

TEST(CircleTest, CircleIsClosedTest)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double radius = 5.0;
    Point point1(x + 10, y - 13, z * 35);
    Point point2(x - 25, y + 3, z - 7);
    Point point3(x * 2, y / 3, z * 3);
    
    Circle circle1(point1, radius);
    Circle circle2(point2, radius + 7);
    Circle cicle3(point3, radius * 2);
    
    bool answer = true;
    ASSERT_EQ(circle1.IsClosed(), answer);
    ASSERT_EQ(circle2.IsClosed(), answer);
    ASSERT_EQ(cicle3.IsClosed(), answer);
}


TEST(CircleTest, CircleTangent)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double aRadius = 5.0;
    double t = 2.0;
    
    
    Point point(x, y, z);
    Circle circle(point, aRadius);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(x, y);
    gp_Dir2d aDir = gp_Dir2d(1, 0);
    
    gp_Ax2d XAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Geom2d_Circle aCircleCascade = Geom2d_Circle(XAxis, aRadius);
    
    gp_Pnt2d aPntAns;
    gp_Vec2d aVecAns;
    
    aCircleCascade.D1(t, aPntAns, aVecAns);
    
    
    ASSERT_NEAR(circle.Tangent(t).X(), aVecAns.X(), TOL);
    ASSERT_NEAR(circle.Tangent(t).Y(), aVecAns.Y(), TOL);
    
}

TEST(IntersectionTest, LineLineIntersectPoint)
{
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    Point O1 = Point(4, 5, 6);
    Point D1 = Point(2, 6, 9);
    
    
    shared_ptr<Line> line1(new Line(O, D));
    shared_ptr<Line> line2(new Line(O1, D1));
    
    Intersection testLine1 = Intersection(line1, line1);
    Intersection testLine2 = Intersection(line1, line2);
    
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 5.0);
    
    gp_Pnt2d aPoint2 = gp_Pnt2d(4.0, 5.0);
    gp_Dir2d aDirLine2 = gp_Dir2d(2.0, 6.0);
    
    Handle(Geom2d_Line) aLine3 = new Geom2d_Line(aPoint1, aDirLine1);
    Handle(Geom2d_Line) aLine4 = new Geom2d_Line(aPoint2, aDirLine2);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLine3, aLine4);
    
    gp_Pnt2d ans = anInter.Point(1);
    
    ASSERT_NEAR(testLine2.FirstPoint().X(), ans.X(), TOL);
    ASSERT_NEAR(testLine2.FirstPoint().Y(), ans.Y(), TOL);
}


TEST(IntersectionTest, LineLineEquivalent)
{
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    
    shared_ptr<Line> line(new Line(O, D));
    
    Intersection testLine = Intersection(line, line);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 5.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aLineCascade);

    cout << anInter.NbSegments();
    
    
    ASSERT_EQ(testLine.CurrentStatus(), Intersection::EQUAL);
    
}

TEST(IntersectionTest, LineLineParallel)
{
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    Point O1 = Point(4, 5, 6);
    
    
    shared_ptr<Line> line(new Line(O, D));
    shared_ptr<Line> line2(new Line(O1, D));
    
    Intersection testLine = Intersection(line, line2);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 5.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aLineCascade);
    
    
    ASSERT_EQ(testLine.NumberInter(), anInter.NbPoints());
    
}

TEST(IntersectionTest, LineCirclePoints1)
{
    Point O = Point(0, 0, 0);
    Point D = Point(1, 0, 0);
    Point center = Point(0, 0, 0);
    
    double aRadius = 5;
    
    shared_ptr<Line> line1(new Line(O, D));
    shared_ptr<Circle> circle1(new Circle(center, aRadius));
    
    Intersection testLine1 = Intersection(line1, circle1);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(0.0, 0.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 0.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(0.0, 0.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Ax2d XAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade = new Geom2d_Circle(XAxis, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aCircleCascade);
    
    gp_Pnt2d ans1 = anInter.Point(1);
    gp_Pnt2d ans2 = anInter.Point(2);
    
    ASSERT_NEAR(testLine1.FirstPoint().X(), ans2.X(), TOL);
    ASSERT_NEAR(testLine1.FirstPoint().Y(), ans2.Y(), TOL);
    ASSERT_NEAR(testLine1.SecondPoint().X(), ans1.X(), TOL);
    ASSERT_NEAR(testLine1.SecondPoint().Y(), ans1.Y(), TOL);
    
    
}

TEST(IntersectionTest, LineCirclePoints2)
{
    Point O = Point(0, 0, 0);
    Point D = Point(1, 0, 0);
    Point center = Point(0, 5, 0);
    double aRadius = 5;
    
    shared_ptr<Line> line1(new Line(O, D));
    shared_ptr<Circle> circle2(new Circle(center, aRadius));
    
    Intersection testLine = Intersection(line1, circle2);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(0.0, 0.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 0.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(0.0, 5.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Ax2d XAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade = new Geom2d_Circle(XAxis, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aCircleCascade);
    
    gp_Pnt2d ans1 = anInter.Point(1);
    
    
    ASSERT_NEAR(fabs(testLine.FirstPoint().X()), ans1.X(), TOL);
    ASSERT_NEAR(fabs(testLine.FirstPoint().Y()), ans1.Y(), TOL);
    
    
}

TEST(IntersectionTest, LineCirclePoints)
{
    Point O = Point(2, 0, 0);
    Point D = Point(5, -3, 0);
    Point center = Point(1, 1, 0);
    
    double aRadius = 1;
    
    shared_ptr<Line> line1(new Line(O, D));
    shared_ptr<Circle> circle1(new Circle(center, aRadius));
    
    Intersection testLine1 = Intersection(line1, circle1);
    
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(2.0, 0.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(5.0, -3.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(1.0, 1.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Ax2d XAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade = new Geom2d_Circle(XAxis, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aCircleCascade);
    
    gp_Pnt2d ans1 = anInter.Point(1);
    gp_Pnt2d ans2 = anInter.Point(2);
    
    ASSERT_NEAR(testLine1.FirstPoint().X(), ans2.X(), TOL);
    ASSERT_NEAR(testLine1.FirstPoint().Y(), ans2.Y(), TOL);
    ASSERT_NEAR(testLine1.SecondPoint().X(), ans1.X(), TOL);
    ASSERT_NEAR(testLine1.SecondPoint().Y(), ans1.Y(), TOL);
    
    
}


TEST(IntersectionTest, LineCircleNotInter)
{
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    Point O1 = Point(100, 200, -100);
    double aRadius = 5;
    
    D.Norm();
    
    shared_ptr<Line> line(new Line(O, D));
    shared_ptr<Circle> circle(new Circle(O1, aRadius));
    
    Intersection testLine = Intersection(line, circle);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 5.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(100.0, 200.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Ax2d XAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade = new Geom2d_Circle(XAxis, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aLineCascade, aCircleCascade);
    
    ASSERT_EQ(testLine.NumberInter(), anInter.NbPoints());
    
}

TEST(IntersectionTest, CircleLineIntersect)
{
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    Point O1 = Point(100, 200, -100);
    double aRadius = 5;
    
    shared_ptr<Line> line(new Line(O, D));
    shared_ptr<Circle> circle(new Circle(O1, aRadius));
    
    Intersection testLine = Intersection(circle, line);
    
    gp_Pnt2d aPoint1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDirLine1 = gp_Dir2d(1.0, 5.0);
    
    Handle(Geom2d_Line) aLineCascade = new Geom2d_Line(aPoint1, aDirLine1);
    
    gp_Pnt2d aPointCascade = gp_Pnt2d(100.0, 200.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Ax2d XAxis = gp_Ax2d(aPointCascade, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade = new Geom2d_Circle(XAxis, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aCircleCascade, aLineCascade);
    
    ASSERT_EQ(testLine.NumberInter(), anInter.NbPoints());
    
}


TEST(IntersectionTest, CircleCirclePoints2)
{
    Point center = Point(0, 0, 0);
    Point center3 = Point(1, 7, 1);
    double aRadius = 5;
    
    shared_ptr<Circle> circle1(new Circle(center, aRadius));
    shared_ptr<Circle> circle3(new Circle(center3, aRadius));
    
    Intersection testLine = Intersection(circle1, circle3);
    
    gp_Pnt2d aPointCascade1 = gp_Pnt2d(0.0, 0.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Pnt2d aPointCascade2 = gp_Pnt2d(1.0, 7.0);
    
    gp_Ax2d XAxis1 = gp_Ax2d(aPointCascade1, aDir);
    gp_Ax2d XAxis2 = gp_Ax2d(aPointCascade2, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade1 = new Geom2d_Circle(XAxis1, aRadius);
    Handle(Geom2d_Circle) aCircleCascade2 = new Geom2d_Circle(XAxis2, aRadius);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aCircleCascade1, aCircleCascade2);
    
    gp_Pnt2d ans1 = anInter.Point(1);
    gp_Pnt2d ans2 = anInter.Point(2);
    
    
    ASSERT_NEAR(testLine.FirstPoint().X(), ans1.X(), TOL);
    ASSERT_NEAR(testLine.FirstPoint().Y(), ans1.Y(), TOL);
    ASSERT_NEAR(testLine.SecondPoint().X(), ans2.X(), TOL);
    ASSERT_NEAR(testLine.SecondPoint().Y(), ans2.Y(), TOL);
}

TEST(IntersectionTest, CircleCircleEqual)
{
    Point O = Point(3, 4, 5);
    double radius = 5.0;
    
    
    shared_ptr<Circle> circle(new Circle(O, radius));
    
    Intersection testLine = Intersection(circle, circle);
    
    ASSERT_EQ(testLine.CurrentStatus(), Intersection::EQUAL);
    
}

TEST(IntersectionTest, CircleCircleNotInter)
{
    Point O = Point(3, 4, 5);
    Point O1 = Point(20, 30, 40);
    double aRadius = 5.0;
    double aRadius1 = 1.0;
    
    
    shared_ptr<Circle> circle(new Circle(O, aRadius));
    shared_ptr<Circle> circle1(new Circle(O1, aRadius1));
    
    Intersection testLine = Intersection(circle, circle1);
    
    gp_Pnt2d aPointCascade1 = gp_Pnt2d(3.0, 4.0);
    gp_Dir2d aDir = gp_Dir2d(1.0, 0.0);
    
    gp_Pnt2d aPointCascade2 = gp_Pnt2d(5.0, 1.0);
    
    gp_Ax2d XAxis1 = gp_Ax2d(aPointCascade1, aDir);
    gp_Ax2d XAxis2 = gp_Ax2d(aPointCascade2, aDir);
    
    
    Handle(Geom2d_Circle) aCircleCascade1 = new Geom2d_Circle(XAxis1, aRadius);
    Handle(Geom2d_Circle) aCircleCascade2 = new Geom2d_Circle(XAxis2, aRadius1);
    
    Geom2dAPI_InterCurveCurve anInter = Geom2dAPI_InterCurveCurve(aCircleCascade1, aCircleCascade2);
    
    
    ASSERT_EQ(testLine.NumberInter(), anInter.NbPoints());
    
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
