// GoogleTest includes
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#include <gtest/gtest.h>

#include <Point.h>
#include <Line.h>
#include <cmath>
#include <Circle.h>

TEST(PointTest, Constructor) {
    double x = 1.0, y = 2.0, z = 3.0;
    Point p(x, y, z);

    static const double tol = 1.e-7;
    ASSERT_NEAR(p.x(), x, tol);
    ASSERT_NEAR(p.y(), y, tol);
    ASSERT_NEAR(p.z(), z, tol);
}

TEST(Line, LineValueTest) {
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    double t = 2.0;
    static const double tol = 1.e-7;
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

TEST(Line, LineIsClosedTest) {
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;

    Point p(x1, y1, z1);
    Point direct(x2, y2, z2);

    Line l(p, direct);

    bool answer = false;
    ASSERT_EQ(l.isClosed(), answer);

}

TEST(Line, LineTangent) {
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    double t = 2.0;
    static const double tol = 1.e-7;

    Point p(x1, y1, z1);
    Point direct(x2, y2, z2);

    Line l(p, direct);

    ASSERT_NEAR(l.tangent(t).x(), x2, tol);
    ASSERT_NEAR(l.tangent(t).y(), y2, tol);
    ASSERT_NEAR(l.tangent(t).z(), z2, tol);

}

TEST(Circle, CircleValueTest) {
    double x = 1.0, y = 2.0, z = 3.0;
    double radius = 5.0;
    double t = 2.0;
    static const double tol = 1.e-7;
    double x_true = x + radius * sin(t);
    double y_true = y + radius * cos(t);
    double z_true = z;
    Point p(x, y, z);

    Circle c(p, radius);

    ASSERT_NEAR(c.Value(t).x(), x_true, tol);
    ASSERT_NEAR(c.Value(t).y(), y_true, tol);
    ASSERT_NEAR(c.Value(t).z(), z_true, tol);

}

TEST(Circle, CircleIsClosedTest) {
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


TEST(Circle, CircleTangent) {
    double x = 1.0, y = 2.0, z = 3.0;
    double radius = 5.0;
    double t = 2.0;

    static const double tol = 1.e-7;

    Point p(x, y, z);
    Circle c(p, radius);

    double x_true = radius * cos(t);
    double y_true = -radius * sin(t);
    double z_true = 0;

    ASSERT_NEAR(c.tangent(t).x(), x_true, tol);
    ASSERT_NEAR(c.tangent(t).y(), y_true, tol);
    ASSERT_NEAR(c.tangent(t).z(), z_true, tol);

}


//=============================================================================
//function : main
//purpose  :
//=============================================================================
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
