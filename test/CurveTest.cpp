// GoogleTest includes
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#include <gtest/gtest.h>

#include <Point.h>

TEST(PointTest, Constructor)
{
  double x = 1.0, y = 2.0, z = 3.0;
  Point p(x, y, z);

  static const double tol = 1.e-7;
  ASSERT_NEAR(p.x(), x, tol);
  ASSERT_NEAR(p.y(), y, tol);
  ASSERT_NEAR(p.z(), z, tol);
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
