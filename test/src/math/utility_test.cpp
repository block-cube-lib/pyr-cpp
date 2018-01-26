#include <pyrite/math/utility.hpp>

#include "gtest/gtest.h"

#include <cmath>

TEST(utility_test, radian_to_degree)
{
  //for(int i = -7200; i < 7200; ++i)
  //{
  //  double const rad = pyrite::math::degree_to_radian(deg);
  //}
}

TEST(utility_test, degree_radian)
{
  using pyrite::math::pi;
  for (int i = -7200; i < 7200; ++i)
  {
    double const deg = i / 10.0;
    double const rad = pyrite::math::degree_to_radian(deg);
    EXPECT_DOUBLE_EQ(rad, pi<double> / 180 * deg);
    EXPECT_DOUBLE_EQ(pyrite::math::radian_to_degree(rad), deg);
  }
}

TEST(utility_test, abs)
{
  using pyrite::math::abs;
  for (int i = -2000; i < 2000; ++i)
  {
    EXPECT_GE(abs(i), 0);
    EXPECT_GE(abs(static_cast<unsigned int>(i)), 0u);
    EXPECT_GE(abs(i / 9.8), 0.0);
  }
}

TEST(utility_test, mod)
{
  using pyrite::math::mod;
  for (int i = -20000; i < 20000; ++i)
  {
    EXPECT_EQ(mod(i, 42), i % 42);

    auto const d = static_cast<double>(i);
    EXPECT_DOUBLE_EQ(mod(d, 9.8), (d - static_cast<int>(d / 9.8) * 9.8));
  }
}

TEST(utility_test, factorial)
{
  using pyrite::math::factorial;
  EXPECT_EQ(factorial<int>(0), 1);
  EXPECT_EQ(factorial<int>(1), 1);

  std::uintmax_t v = 1;
  for (std::uintmax_t i = 2; i < 21; ++i)
  {
    v *= i;
    EXPECT_EQ(factorial<std::uintmax_t>(i), v);
    EXPECT_DOUBLE_EQ(factorial<double>(i), static_cast<double>(v));
  }
}

TEST(utility_test, power)
{
  using pyrite::math::power;
  std::uintmax_t x = 2;
  EXPECT_EQ(power(x, 0), 1u);

  std::uintmax_t v = 1;
  for (std::uintmax_t i = 1; i < 10; ++i)
  {
    v *= x;
    EXPECT_EQ(power(x, i), v);
  }
}

template <typename T>
void sin_check(T rad)
{
  auto ss = std::sin(rad);
  auto ps = pyrite::math::sin(rad);
  EXPECT_LE(pyrite::math::abs(ps - ss), static_cast<T>(0.000001));
}

TEST(utility_test, sin)
{
  using pyrite::math::degree_to_radian;
  for (int i = -7200; i < 7200; ++i)
  {
    auto const rad = degree_to_radian(i / 10.0l);
    sin_check(static_cast<float>(rad));
    sin_check(static_cast<double>(rad));
    sin_check(rad);
  }
}
