/// GoogleTest includes
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#include <gtest/gtest.h>

// Includes from Core.
#include <Vector.h>
#include <Point.h>
#include <Line.h>

static const double EPS = 1.e-10;
static const double THE_TOLERANCE = 1.e-7;

// Нулевое направление у линии
TEST(Line, Construct)
{
  Vector v(0.0, 0.0);
  ASSERT_ANY_THROW(Line(0.0, 0.0, v));
}

// Значения точки по умолчанию
TEST(Point, ConstructEmpty)
{
  Point p;
  EXPECT_NEAR(p.getX(), 0.0, EPS);
  EXPECT_NEAR(p.getY(), 0.0, EPS);
}
