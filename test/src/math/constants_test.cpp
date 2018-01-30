#include <pyrite/math/constants.hpp>
#include <pyrite/math/literals/constants_literals.hpp>

#include "gtest/gtest.h"

using namespace pyrite::math;

TEST(constants_test, pi)
{
  constexpr auto value = 3.1415926535897932384626433l;
  EXPECT_FLOAT_EQ(pi<float>, static_cast<float>(value));
  EXPECT_DOUBLE_EQ(pi<double>, static_cast<double>(value));
  EXPECT_DOUBLE_EQ(pi<long double>, value);
}

TEST(constants_test, pi_literals)
{
  using namespace pyrite::math::literals;

  // _pi
  EXPECT_DOUBLE_EQ(42_pi, 42 * pi<double>);
  EXPECT_DOUBLE_EQ(42.1_pi, 42.1 * pi<double>);

  // pif
  EXPECT_FLOAT_EQ(42_pif, 42.0f * pi<float>);
  EXPECT_FLOAT_EQ(42.1_pif, 42.1f * pi<float>);

  // pil
  EXPECT_DOUBLE_EQ(42_pil, 42.0l * pi<long double>);
  EXPECT_DOUBLE_EQ(42.1_pil, 42.1l * pi<long double>);
}
