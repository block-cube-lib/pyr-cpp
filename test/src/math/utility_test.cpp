#include <pyrite/math/utility.hpp>

#include "gtest/gtest.h"

#include <cmath>

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

TEST(utility_test, sqrt)
{
  for (int i = 0; i < 100000; ++i)
  {
    auto const s  = i / 10.0l;
    auto       ss = std::sqrtl(s);
    auto       ps = pyrite::math::sqrt(s);
    EXPECT_LE(pyrite::math::abs(ps - ss), 0.000001l);
  }
}

template <typename T>
void sin_check(T rad)
{
  using pyrite::math::abs;
  auto const ps = pyrite::math::sin(rad);
  auto const ss = std::sin(rad);
  EXPECT_LE(abs(ss - ps), 0.000001l);
}

TEST(utility_test, sin)
{
  using pyrite::math::degree_to_radian;
  for (int i = -72000; i < 72000; ++i)
  {
    auto const rad = degree_to_radian(i / 100.0l);
    sin_check(static_cast<float>(rad));
    sin_check(static_cast<double>(rad));
    sin_check(rad);
  }

  constexpr auto rad = degree_to_radian(42.2l);
  constexpr auto s   = pyrite::math::sin(rad);
  EXPECT_LE(pyrite::math::abs(s - std::sin(rad)), 0.00001l);
}

template <typename T>
void cos_check(T rad)
{
  auto pc = pyrite::math::cos(rad);
  auto sc = std::cos(rad);
  EXPECT_LE(abs(sc - pc), 0.000001l);
}

TEST(utility_test, cos)
{
  using pyrite::math::degree_to_radian;
  for (int i = -72000; i < 72000; ++i)
  {
    auto const rad = degree_to_radian(i / 100.0l);
    sin_check(static_cast<float>(rad));
    sin_check(static_cast<double>(rad));
    sin_check(rad);
  }

  constexpr auto rad = degree_to_radian(42.2l);
  constexpr auto c   = pyrite::math::cos(rad);
  EXPECT_LE(abs(c - std::cos(rad)), 0.000001l);
}

TEST(utility_test, sincos)
{
  using pyrite::math::degree_to_radian;
  for (int i = -72000; i < 72000; ++i)
  {
    using pyrite::math::abs;
    auto const x      = degree_to_radian(i / 100.0l);
    auto const [s, c] = pyrite::math::sincos(x);
    EXPECT_LE(abs(s - std::sin(x)), 0.000001l);
    EXPECT_LE(abs(c - pyrite::math::cos(x)), 0.000001l);
  }
}

TEST(utility_test, tan)
{
  using pyrite::math::abs;
  using pyrite::math::degree_to_radian;
  using pyrite::math::equal;

  auto const deg_tan = [](auto deg) {
    auto const rad = degree_to_radian(deg);
    return pyrite::math::tan(rad);
  };

  EXPECT_TRUE(equal(deg_tan(0), 0.0));
  EXPECT_TRUE(equal(deg_tan(180), 0.0));
  EXPECT_TRUE(equal(deg_tan(360), 0.0));

  EXPECT_TRUE(equal(deg_tan(45.0l), 1.0l));
  EXPECT_TRUE(equal(deg_tan(135.0l), -1.0l));
  EXPECT_TRUE(equal(deg_tan(225.0l), 1.0l));
  EXPECT_TRUE(equal(deg_tan(315.0l), -1.0l));
}

TEST(utility_test, asin)
{
  using namespace pyrite::math;
  for (int i = -7200; i < 7200; ++i)
  {
    auto const x = static_cast<double>(i) / 10;
    SCOPED_TRACE(std::to_string(x));
    auto const rad = degree_to_radian<double>(x);
    auto const s   = std::sin(rad);
    EXPECT_NEAR(std::asin(s), pyrite::math::asin(s), 0.000001);
  }
}
