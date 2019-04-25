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

TEST(PointTest, Constructor) {
    double x = 1.0, y = 2.0, z = 3.0;
    Point p(x, y, z);

    ASSERT_NEAR(p.x(), x, tol);
    ASSERT_NEAR(p.y(), y, tol);
    ASSERT_NEAR(p.z(), z, tol);
}

TEST(PointTest, OperatorPlusVector) {
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = -1.0, y2 = -5.0, z2 = 10.0;
    Point P1 = Point(x1, y1, z1);
    Point P2 = Point(x2, y2, z2);

    ASSERT_NEAR((P1 + P2).x(), x1 + x2, tol);
    ASSERT_NEAR((P1 + P2).y(), y1 + y2, tol);
    ASSERT_NEAR((P1 + P2).z(), z1 + z2, tol);

    ASSERT_NEAR((P2 + P1).x(), x2 + x1, tol);
    ASSERT_NEAR((P2 + P1).y(), y2 + y1, tol);
    ASSERT_NEAR((P2 + P1).z(), z2 + z1, tol);


}

TEST(PointTest, OperatorMul) {
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double t = 5;
    Point P1 = Point(x1, y1, z1);

    ASSERT_NEAR((P1 * t).x(), x1 * t, tol);
    ASSERT_NEAR((P1 * t).y(), y1 * t, tol);
    ASSERT_NEAR((P1 * t).z(), z1 * t, tol);


}

TEST(PointTest, OperatorSumScaler) {
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double t = 5;
    Point P1 = Point(x1, y1, z1);

    ASSERT_NEAR((P1 + t).x(), x1 + t, tol);
    ASSERT_NEAR((P1 + t).y(), y1 + t, tol);
    ASSERT_NEAR((P1 + t).z(), z1 + t, tol);


}

TEST(LineTest, LineValueTest) {
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    double t = 2.0;

    double x_true = x1 + x2 * t;
    double y_true = y1 + y2 * t;
    double z_true = z1 + z2 * t;

    Point p(x1, y1, z1);
    Point direct(x2, y2, z2);

    Line l(p, direct);

    ASSERT_NEAR(l.Value(t).x(), x_true, tol);
    ASSERT_NEAR(l.Value(t).y(), y_true, tol);
    ASSERT_NEAR(l.Value(t).z(), z_true, tol);

}

TEST(LineTest, LineIsClosedTest) { // NOLINT(cert-err58-cpp)
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;

    Point p(x1, y1, z1);
    Point direct(x2, y2, z2);

    Line l(p, direct);

    bool answer = false;
    ASSERT_EQ(l.isClosed(), answer);

}

TEST(LineTest, LineTangent) {
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    double t = 2.0;


    Point p(x1, y1, z1);
    Point direct(x2, y2, z2);

    Line l(p, direct);

    ASSERT_NEAR(l.tangent(t).x(), x2, tol);
    ASSERT_NEAR(l.tangent(t).y(), y2, tol);
    ASSERT_NEAR(l.tangent(t).z(), z2, tol);

}

TEST(CircleTest, CircleValueTest) {
    double x = 1.0, y = 2.0, z = 3.0;
    double radius = 5.0;
    double t = 2.0;

    double x_true = x + radius * cos(t);
    double y_true = y + radius * sin(t);
    double z_true = z;
    Point p(x, y, z);

    Circle c(p, radius);

    ASSERT_NEAR(c.Value(t).x(), x_true, tol);
    ASSERT_NEAR(c.Value(t).y(), y_true, tol);
    ASSERT_NEAR(c.Value(t).z(), z_true, tol);

}

TEST(CircleTest, CircleIsClosedTest) {
    double x = 1.0, y = 2.0, z = 3.0;
    double radius = 5.0;
    Point p1(x + 10, y - 13, z * 35);
    Point p2(x - 25, y + 3, z - 7);
    Point p3(x * 2, y / 3, z * 3);

    Circle c1(p1, radius);
    Circle c2(p2, radius + 7);
    Circle c3(p3, radius * 2);

    bool answer = true;
    ASSERT_EQ(c1.isClosed(), answer);
    ASSERT_EQ(c2.isClosed(), answer);
    ASSERT_EQ(c3.isClosed(), answer);
}


TEST(CircleTest, CircleTangent) {
    double x = 1.0, y = 2.0, z = 3.0;
    double radius = 5.0;
    double t = 2.0;


    Point p(x, y, z);
    Circle c(p, radius);

    double x_true = -radius * sin(t);
    double y_true = radius * cos(t);
    double z_true = 0;

    ASSERT_NEAR(c.tangent(t).x(), x_true, tol);
    ASSERT_NEAR(c.tangent(t).y(), y_true, tol);
    ASSERT_NEAR(c.tangent(t).z(), z_true, tol);

}

TEST(IntersectionTest, LineLine) {
    Point O = Point(3, 4, 5);
    Point D = Point(1, 5, 8);
    Point O1 = Point(4, 5, 6);
    Point D1 = Point(2, 6, 9);


    shared_ptr<Line> line(new Line(O, D));
    shared_ptr<Line> line2(new Line(O1, D1));

    Intersection test_line1 = Intersection(line, line);
    Intersection test_line2 = Intersection(line, line2);

    double x_true2 = 2, y_true2 = -1;

//
//    ASSERT_EQ(test_line1.First_Point().x(), x_true1);
//    ASSERT_EQ(test_line1.First_Point().y(), y_true1);

    ASSERT_EQ(test_line2.First_Point().x(), x_true2);
    ASSERT_EQ(test_line2.First_Point().y(), y_true2);


}

TEST(IntersectionTest, LineCircle) {
    Point O = Point(0, 0, 0);
    Point D = Point(1, 0, 0);
    Point center = Point(0, 0, 0);
    Point center2 = Point(0, 5, 0);
    Point center3 = Point(0, 6, 0);
    double radius1 = 5;

    shared_ptr<Line> line1(new Line(O, D));
    shared_ptr<Circle> circle1(new Circle(center, radius1));
    shared_ptr<Circle> circle2(new Circle(center2, radius1));
    shared_ptr<Circle> circle3(new Circle(center3, radius1));


    Point O1 = Point(4, 5, 6);
    Point D1 = Point(2, 6, 9);


    shared_ptr<Line> line2(new Line(O1, D1));

    Intersection test_line1 = Intersection(line1, circle1);
    Intersection test_line2 = Intersection(line1, circle2);
    Intersection test_line3 = Intersection(line1, circle3);


    double x_true2 = -5, y_true2 = 0;
    double x_true3 = 5, y_true3 = 0;

    double x_true4 = 0, y_true4 = 5;


    ASSERT_NEAR(test_line1.First_Point().x(), x_true2, tol);
    ASSERT_NEAR(test_line1.First_Point().y(), y_true2, tol);
    ASSERT_NEAR(test_line1.Second_Point().x(), x_true3, tol);
    ASSERT_NEAR(test_line1.Second_Point().y(), y_true3, tol);

    ASSERT_NEAR(abs(test_line2.First_Point().x()), x_true4, tol);
    ASSERT_NEAR(abs(test_line2.First_Point().y()), y_true4, tol);


}

TEST(IntersectionTest, CircleCircle) {
    Point center = Point(0, 0, 0);
    Point center2 = Point(0, 10, 0);
    Point center3 = Point(1, 7, 1);
    double radius1 = 5;

    shared_ptr<Circle> circle1(new Circle(center, radius1));
    shared_ptr<Circle> circle2(new Circle(center2, radius1));
    shared_ptr<Circle> circle3(new Circle(center3, radius1));


    Intersection test_line1 = Intersection(circle1, circle1);
    Intersection test_line2 = Intersection(circle1, circle2);
    Intersection test_line3 = Intersection(circle1, circle3);

    double x_true2 = 0, y_true2 = 5;
    double x_true3 = 4, y_true3 = 3;
    double x_true4 = -3, y_true4 = 4;


    ASSERT_NEAR(test_line2.First_Point().x(), x_true2, tol);
    ASSERT_NEAR(test_line2.First_Point().y(), y_true2, tol);

    ASSERT_NEAR(test_line3.First_Point().x(), x_true3, tol);
    ASSERT_NEAR(test_line3.First_Point().y(), y_true3, tol);
    ASSERT_NEAR(test_line3.Second_Point().x(), x_true4, tol);
    ASSERT_NEAR(test_line3.Second_Point().y(), y_true4, tol);
}


//=============================================================================
//function : main
//purpose  :
//=============================================================================
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#pragma clang diagnostic pop