// GoogleTest includes
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#include <gtest/gtest.h>

#include <Equation.h>

static const double THE_TOLERANCE = 1.e-7;

TEST(EquationTest, TwoSolutions)
{
  double A = 1.0, B = -3.0, C = 2.0;
  SquareEquation anEq(A, B, C);

  ASSERT_EQ(anEq.NbSolutions(), 2);
  ASSERT_NEAR(anEq.Solution(0), 1.0, THE_TOLERANCE);
  ASSERT_NEAR(anEq.Solution(1), 2.0, THE_TOLERANCE);
}

TEST(EquationTest, OneSolution)
{
  double A = 1.0, B = 2.0, C = 1.0;
  SquareEquation anEq(A, B, C);

  ASSERT_EQ(anEq.NbSolutions(), 1);
  ASSERT_NEAR(anEq.Solution(0), -1.0, THE_TOLERANCE);
}

TEST(EquationTest, ZeroSolutions)
{
  double A = 1.0, B = 1.0, C = 2.0;
  SquareEquation anEq(A, B, C);

  ASSERT_EQ(anEq.NbSolutions(), 0);
}

TEST(EquationTest, ThrowWrongIndex)
{
  double A = 1.0, B = 1.0, C = 2.0;
  SquareEquation anEq(A, B, C);

  ASSERT_EQ(anEq.NbSolutions(), 0);
  ASSERT_ANY_THROW(anEq.Solution(0));
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
