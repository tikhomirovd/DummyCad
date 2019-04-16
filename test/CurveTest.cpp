// GoogleTest includes
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#include <gtest/gtest.h>

#include <Point.h>
#include <Line.h>

TEST(PointTest, Constructor)
{
  double x = 1.0, y = 2.0, z = 3.0;
  Point p(x, y, z);

  static const double tol = 1.e-7;
  ASSERT_NEAR(p.x(), x, tol);
  ASSERT_NEAR(p.y(), y, tol);
  ASSERT_NEAR(p.z(), z, tol);
}

TEST(LineValueTest, Line) {
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 2.0, y2 = 3.0, z2 = 3.0;
    static const double tol = 1.e-7, t = 2;
    double x_true = x1 + x2  * t;
    double y_true = y1 + y2  * t;
    double z_true = z1 + z2  * t;

    Point p(x1, y1, z1);
    Point direct(x2, y2, z2);


    Point d_true(x1 + x2 * t, y1 + y2 * t, z1 + z2 * t);
    Line l(p, direct);

    ASSERT_NEAR(l.Value(t).x(), x_true, tol);
    ASSERT_NEAR(l.Value(t).y(), y_true, tol);
    ASSERT_NEAR(l.Value(t).z(), z_true, tol);

}


//=============================================================================
//function : main
//purpose  :
//=============================================================================
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
