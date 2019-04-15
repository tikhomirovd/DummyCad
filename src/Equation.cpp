#include "Equation.h"

#include <cmath>
#include <exception>

SquareEquation::SquareEquation(const double A, const double B, const double C)
  : myNbSol(0)
{
  static const double THE_TOLERANCE = 1.e-7;
  static const double THE_SQUARE_TOL = THE_TOLERANCE * THE_TOLERANCE;

  double D = B * B - 4.0 * A * C;
  if (D > THE_SQUARE_TOL)
    myNbSol = 2;
  if (fabs(D) < THE_SQUARE_TOL)
  {
    D = 0.0;
    myNbSol = 1;
  }
  if (D >= 0.0)
  {
    mySolutions[0] = (-B - sqrt(D)) / (2.0 * A);
    mySolutions[1] = (-B + sqrt(D)) / (2.0 * A);
  }
}

int SquareEquation::NbSolutions() const
{
  return myNbSol;
}

double SquareEquation::Solution(const int theIndex) const
{
  if (theIndex >= myNbSol)
    throw std::exception("Index is greater than nuber of solutions");
  return mySolutions[theIndex];
}
