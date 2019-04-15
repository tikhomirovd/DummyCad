#pragma once

#include "Defines.h"

//! \brief Solves square equation by the given parameters
//!
//! Square equation:
//! \f[
//!   A x^2 + B x + C = 0
//! \f]
class Equation_EXPORT SquareEquation {
public:
  //! Constructor
  SquareEquation(const double A, const double B, const double C);

  //! \brief Number of solutions. Negative value means that each real value is a solution.
  int NbSolutions() const;

  //! \brief Return solution by its index.
  //!        Throws exception if the index is greater than number of solutions.
  double Solution(const int theIndex) const;

private:
  int myNbSol; //!< Number of solutions
  double mySolutions[2]; //!< Solutions of square equation
};
