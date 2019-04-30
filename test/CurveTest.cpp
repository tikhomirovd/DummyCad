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

static const double tol = 1.e-7;


TEST(PointTest, Constructor)
{
    double x = 1.0, y = 2.0, z = 3.0;
    Point point(x, y, z);
    
    ASSERT_NEAR(point.X(), x, tol);
    ASSERT_NEAR(point.Y(), y, tol);
    ASSERT_NEAR(point.Z(), z, tol);
}

TEST(PointTest, OperatorPlusVector)
{
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = -1.0, y2 = -5.0, z2 = 10.0;
    Point point1 = Point(x1, y1, z1);
    Point point2 = Point(x2, y2, z2);
    
    ASSERT_NEAR((point1 + point2).X(), x1 + x2, tol);
    ASSERT_NEAR((point1 + point2).Y(), y1 + y2, tol);
    ASSERT_NEAR((point1 + point2).Z(), z1 + z2, tol);
    
    ASSERT_NEAR((point2 + point1).X(), x2 + x1, tol);
    ASSERT_NEAR((point2 + point1).Y(), y2 + y1, tol);
    ASSERT_NEAR((point2 + point1).Z(), z2 + z1, tol);
    
    
}

TEST(PointTest, OperatorMul)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double t = 5;
    Point point = Point(x, y, z);
    
    ASSERT_NEAR((point * t).X(), x * t, tol);
    ASSERT_NEAR((point * t).Y(), y * t, tol);
    ASSERT_NEAR((point * t).Z(), z * t, tol);
    
    
}

TEST(PointTest, OperatorSumScaler)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double t = 5;
    Point point = Point(x, y, z);
    
    ASSERT_NEAR((point + t).X(), x + t, tol);
    ASSERT_NEAR((point + t).Y(), y + t, tol);
    ASSERT_NEAR((point + t).Z(), z + t, tol);
    
    
}

TEST(LineTest, LineValueTest)
{
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    double t = 2.0;
    
    double xTrue = x1 + x2 * t;
    double yTrue = y1 + y2 * t;
    double zTrue = z1 + z2 * t;
    
    Point point(x1, y1, z1);
    Point direct(x2, y2, z2);
    
    Line line(point, direct);
    
    ASSERT_NEAR(line.Value(t).X(), xTrue, tol);
    ASSERT_NEAR(line.Value(t).Y(), yTrue, tol);
    ASSERT_NEAR(line.Value(t).Z(), zTrue, tol);
    
}

TEST(LineTest, LineIsClosedTest)
{ // NOLINT(cert-err58-cpp)
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    
    Point point(x1, y1, z1);
    Point direct(x2, y2, z2);
    
    Line l(point, direct);
    
    bool answer = false;
    ASSERT_EQ(l.IsClosed(), answer);
    
}

TEST(LineTest, LineTangent)
{
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    double t = 2.0;
    
    
    Point point(x1, y1, z1);
    Point direct(x2, y2, z2);
    
    Line l(point, direct);
    
    ASSERT_NEAR(l.Tangent(t).X(), x2, tol);
    ASSERT_NEAR(l.Tangent(t).Y(), y2, tol);
    ASSERT_NEAR(l.Tangent(t).Z(), z2, tol);
    
}

TEST(CircleTest, CircleValueTest)
{
    double x = 1.0, y = 2.0, z = 3.0;
    double radius = 5.0;
    double t = 2.0;
    
    double xTrue = x + radius * cos(t);
    double yTrue = y + radius * sin(t);
    double zTrue = z;
    Point point(x, y, z);
    
    Circle circle(point, radius);
    
    ASSERT_NEAR(circle.Value(t).X(), xTrue, tol);
    ASSERT_NEAR(circle.Value(t).Y(), yTrue, tol);
    ASSERT_NEAR(circle.Value(t).Z(), zTrue, tol);
    
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
    double radius = 5.0;
    double t = 2.0;
    
    
    Point point(x, y, z);
    Circle circle(point, radius);
    
    double xTrue = -radius * sin(t);
    double yTrue = radius * cos(t);
    double zTrue = 0;
    
    ASSERT_NEAR(circle.Tangent(t).X(), xTrue, tol);
    ASSERT_NEAR(circle.Tangent(t).Y(), yTrue, tol);
    ASSERT_NEAR(circle.Tangent(t).Z(), zTrue, tol);
    
}

TEST(IntersectionTest, LineLineIntersectPoint)
{
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    Point O1 = Point(4, 5, 6);
    Point D1 = Point(2, 6, 9);
    
    
    shared_ptr<Line> line(new Line(O, D));
    shared_ptr<Line> line2(new Line(O1, D1));
    
    Intersection testLine1 = Intersection(line, line);
    Intersection testLine2 = Intersection(line, line2);
    
    double xTrue2 = 2, yTrue2 = -1;
    
    ASSERT_EQ(testLine2.FirstPoint().X(), xTrue2);
    ASSERT_EQ(testLine2.FirstPoint().Y(), yTrue2);
}

TEST(IntersectionTest, LineLineEquivalent)
{
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    
    shared_ptr<Line> line(new Line(O, D));
    
    Intersection testLine = Intersection(line, line);
    
    
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
    
    ASSERT_EQ(testLine.CurrentStatus(), Intersection::NOT_INTERSECTED);
    
}

TEST(IntersectionTest, LineCirclePoints)
{
    Point O = Point(0, 0, 0);
    Point D = Point(1, 0, 0);
    Point center = Point(0, 0, 0);
    Point center2 = Point(0, 5, 0);
    Point center3 = Point(0, 6, 0);
    double radius = 5;
    
    shared_ptr<Line> line1(new Line(O, D));
    shared_ptr<Circle> circle1(new Circle(center, radius));
    shared_ptr<Circle> circle2(new Circle(center2, radius));
    shared_ptr<Circle> circle3(new Circle(center3, radius));
    
    
    Intersection testLine1 = Intersection(line1, circle1);
    Intersection testLine2 = Intersection(line1, circle2);
    Intersection testLine3 = Intersection(line1, circle3);
    
    
    double xTrue2 = -5, yTrue2 = 0;
    double xTrue3 = 5, yTrue3 = 0;
    
    double xTrue4 = 0, yTrue4 = 5;
    
    
    ASSERT_NEAR(testLine1.FirstPoint().X(), xTrue2, tol);
    ASSERT_NEAR(testLine1.FirstPoint().Y(), yTrue2, tol);
    ASSERT_NEAR(testLine1.SecondPoint().X(), xTrue3, tol);
    ASSERT_NEAR(testLine1.SecondPoint().Y(), yTrue3, tol);
    
    ASSERT_NEAR(fabs(testLine2.FirstPoint().X()), xTrue4, tol);
    ASSERT_NEAR(fabs(testLine2.FirstPoint().Y()), yTrue4, tol);
    
    
}

TEST(IntersectionTest, LineCircleNotInter)
{
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    Point O1 = Point(100, 200, -100);
    double radius = 5;
    
    shared_ptr<Line> line(new Line(O, D));
    shared_ptr<Circle> circle(new Circle(O1, radius));
    
    Intersection testLine = Intersection(line, circle);
    
    ASSERT_EQ(testLine.CurrentStatus(), Intersection::NOT_INTERSECTED);
    
}

TEST(IntersectionTest, CircleCirclePoints)
{
    Point center = Point(0, 0, 0);
    Point center2 = Point(0, 10, 0);
    Point center3 = Point(1, 7, 1);
    double radius = 5;
    
    shared_ptr<Circle> circle1(new Circle(center, radius));
    shared_ptr<Circle> circle2(new Circle(center2, radius));
    shared_ptr<Circle> circle3(new Circle(center3, radius));
    
    
    Intersection testLine1 = Intersection(circle1, circle1);
    Intersection testLine2 = Intersection(circle1, circle2);
    Intersection testLine3 = Intersection(circle1, circle3);
    
    double xTrue2 = 0, yTrue2 = 5;
    double xTrue3 = 4, yTrue3 = 3;
    double xTrue4 = -3, yTrue4 = 4;
    
    
    ASSERT_NEAR(testLine2.FirstPoint().X(), xTrue2, tol);
    ASSERT_NEAR(testLine2.FirstPoint().Y(), yTrue2, tol);
    
    ASSERT_NEAR(testLine3.FirstPoint().X(), xTrue3, tol);
    ASSERT_NEAR(testLine3.FirstPoint().Y(), yTrue3, tol);
    ASSERT_NEAR(testLine3.SecondPoint().X(), xTrue4, tol);
    ASSERT_NEAR(testLine3.SecondPoint().Y(), yTrue4, tol);
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
    double radius = 5.0;
    double radius1 = 1.0;
    
    
    shared_ptr<Circle> circle(new Circle(O, radius));
    shared_ptr<Circle> circle1(new Circle(O1, radius1));
    
    Intersection testLine = Intersection(circle, circle1);
    
    
    ASSERT_EQ(testLine.CurrentStatus(), Intersection::NOT_INTERSECTED);
    
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