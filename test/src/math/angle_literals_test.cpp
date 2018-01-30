#include <pyrite/math/literals/angle_literals.hpp>

#include "gtest/gtest.h"

namespace
{
using namespace pyrite::math;
using namespace pyrite::math::literals;

TEST(angle_literals_test, rad)
{
  constexpr angle<double>      a = 42.0_rad;
  constexpr angle<float>       b = 42.0_radf;
  constexpr angle<long double> c = 42.0_radl;
  constexpr angle<double>      d = 42_rad;
  constexpr angle<float>       e = 42_radf;
  constexpr angle<long double> f = 42_radl;

  EXPECT_DOUBLE_EQ(a.radian(), 42);
  EXPECT_FLOAT_EQ(b.radian(), 42);
  EXPECT_DOUBLE_EQ(c.radian(), 42);
  EXPECT_DOUBLE_EQ(d.radian(), 42);
  EXPECT_FLOAT_EQ(e.radian(), 42);
  EXPECT_DOUBLE_EQ(f.radian(), 42);
}

TEST(angle_literals_test, deg)
{
  constexpr angle<double>      a = 42.0_deg;
  constexpr angle<float>       b = 42.0_degf;
  constexpr angle<long double> c = 42.0_degl;
  constexpr angle<double>      d = 42_deg;
  constexpr angle<float>       e = 42_degf;
  constexpr angle<long double> f = 42_degl;

  EXPECT_DOUBLE_EQ(a.degree(), 42);
  EXPECT_FLOAT_EQ(b.degree(), 42);
  EXPECT_DOUBLE_EQ(c.degree(), 42);
  EXPECT_DOUBLE_EQ(d.degree(), 42);
  EXPECT_FLOAT_EQ(e.degree(), 42);
  EXPECT_DOUBLE_EQ(f.degree(), 42);
}

TEST(angle_literals_test, pi_rad)
{
  constexpr angle<double>      a = 42.0_pi_rad;
  constexpr angle<float>       b = 42.0_pi_radf;
  constexpr angle<long double> c = 42.0_pi_radl;
  constexpr angle<double>      d = 42_pi_rad;
  constexpr angle<float>       e = 42_pi_radf;
  constexpr angle<long double> f = 42_pi_radl;

  EXPECT_DOUBLE_EQ(a.radian(), 42 * pi<double>);
  EXPECT_FLOAT_EQ(b.radian(), 42 * pi<float>);
  EXPECT_DOUBLE_EQ(c.radian(), 42 * pi<long double>);
  EXPECT_DOUBLE_EQ(d.radian(), 42 * pi<double>);
  EXPECT_FLOAT_EQ(e.radian(), 42 * pi<float>);
  EXPECT_DOUBLE_EQ(f.radian(), 42 * pi<long double>);
}

} // namespace
