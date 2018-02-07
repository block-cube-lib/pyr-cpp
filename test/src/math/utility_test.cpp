#include <pyrite/math/utility.hpp>

#include "math/utility_test.h"

#include <cmath>
#include <type_traits>

namespace floating_point_type_only_test
{
TYPED_TEST_CASE_P(math_utility_test);

TYPED_TEST_P(math_utility_test, degree_radian)
{
  using namespace pyrite::math;
  using value_type = typename TestFixture::value_type;

  TestFixture::loop(
    [](int i) {
      value_type const deg = static_cast<value_type>(i) / 10;
      value_type const rad = degree_to_radian(deg);
      TestFixture::equal(rad, pi<value_type> / 180 * deg);
      TestFixture::equal(radian_to_degree(rad), deg);
    },
    -7200,
    7200);
}

TYPED_TEST_P(math_utility_test, sqrt)
{
  using value_type = typename TestFixture::value_type;
  TestFixture::loop(
    [](int i) {
      auto const s  = static_cast<value_type>(i) / 100;
      auto const ss = std::sqrt(s);
      auto const ps = pyrite::math::sqrt(s);
      TestFixture::equal(ps, ss);
    },
    0,
    1000000);
}

TYPED_TEST_P(math_utility_test, sin)
{
  using value_type = typename TestFixture::value_type;
  TestFixture::loop(
    [](int i) {
      auto const rad =
        pyrite::math::degree_to_radian(static_cast<value_type>(i) / 100);
      auto const ps = pyrite::math::sin(rad);
      auto const ss = std::sin(rad);
      TestFixture::near(ss, ps);
    },
    -72000,
    72000);
}

TYPED_TEST_P(math_utility_test, cos)
{
  using value_type = typename TestFixture::value_type;
  TestFixture::loop(
    [](int i) {
      auto const rad =
        pyrite::math::degree_to_radian(static_cast<value_type>(i) / 100);
      auto const pc = pyrite::math::cos(rad);
      auto const sc = std::cos(rad);
      TestFixture::near(sc, pc);
    },
    -72000,
    72000);
}

TYPED_TEST_P(math_utility_test, sincos)
{
  using pyrite::math::power;
  using value_type = typename TestFixture::value_type;
  TestFixture::loop(
    [](int i) {
      auto const rad =
        pyrite::math::degree_to_radian(static_cast<value_type>(i) / 100);
      auto const [s, c] = pyrite::math::sincos(rad);
      TestFixture::near(pyrite::math::sin(rad), s);
      TestFixture::near(pyrite::math::cos(rad), c);
      TestFixture::near(power(s, 2) + power(c, 2), value_type{1});
    },
    -72000,
    72000);
}

TYPED_TEST_P(math_utility_test, tan)
{
  using pyrite::math::abs;
  using value_type = typename TestFixture::value_type;

  TestFixture::loop(
    [](int i) {
      if (abs(i) % 180 != 90)
      {
        auto const rad =
          pyrite::math::degree_to_radian(static_cast<value_type>(i));
        auto const pt = pyrite::math::tan(rad);
        auto const st = std::tan(rad);
        TestFixture::near(pt, st);
      }
    },
    -720,
    720);
}

TYPED_TEST_P(math_utility_test, asin)
{
  using pyrite::math::power;
  using value_type = typename TestFixture::value_type;
  TestFixture::loop(
    [](int i) {
      auto const x   = static_cast<value_type>(i) / 10;
      auto const rad = pyrite::math::degree_to_radian(x);
      auto const s   = std::sin(rad);
      TestFixture::near(std::asin(s), pyrite::math::asin(s));
    },
    -72000,
    72000);
}

REGISTER_TYPED_TEST_CASE_P(math_utility_test,
                           degree_radian,
                           sqrt,
                           sin,
                           cos,
                           sincos,
                           tan,
                           asin);
using test_case = ::testing::Types<float, double, long double>;
INSTANTIATE_TYPED_TEST_CASE_P(floating_point_type_only_test,
                              math_utility_test,
                              test_case);
} // namespace floating_point_type_only_test

namespace need_integer_test
{
TYPED_TEST_CASE_P(math_utility_test);

TYPED_TEST_P(math_utility_test, abs)
{
  using value_type = typename TestFixture::value_type;
  TestFixture::loop(
    [](int i) {
      auto const a = static_cast<value_type>(i) / 10;
      auto const b = a < 0 ? -a : a;
      TestFixture::equal(pyrite::math::abs(a), b);
    },
    -2000,
    2000);
}

TYPED_TEST_P(math_utility_test, mod)
{
  using value_type = typename TestFixture::value_type;
  TestFixture::loop(
    [](int i) {
      if constexpr (std::is_integral_v<value_type>)
      {
        TestFixture::equal(pyrite::math::mod(i, 42), i % 42);
      }
      else
      {
        auto const v = static_cast<double>(i);
        TestFixture::equal(pyrite::math::mod(v, 9.8),
                           (v - static_cast<std::intmax_t>(v / 9.8) * 9.8));
      }
    },
    -20000,
    20000);
}

TYPED_TEST_P(math_utility_test, factorial)
{
  using value_type = typename TestFixture::value_type;
  using namespace pyrite;
  using pyrite::math::factorial;

  TestFixture::equal(factorial<value_type>(0), value_type{1});
  TestFixture::equal(factorial<value_type>(1), value_type{1});

  auto check = [](u64 max) {
    std::conditional_t<std::is_integral_v<value_type>, u64, f64> result{1};
    for (u64 i = 2; i <= max; ++i)
    {
      result *= i;
    }
    return result;
  };

  TestFixture::loop(
    [&](u64 i) {
      auto const v = factorial<value_type>(i);
      auto const c = check(i);
      TestFixture::equal(v, c);
      ::testing::StaticAssertTypeEq<std::remove_const_t<decltype(v)>,
                                    value_type>();
    },
    2u,
    8u + 1u);
}

TYPED_TEST_P(math_utility_test, power)
{
  using value_type = typename TestFixture::value_type;
  using namespace pyrite;
  using pyrite::math::power;

  TestFixture::loop2(
    [&](int i, int j) {
      auto const x      = static_cast<value_type>(i);
      auto const v      = power(x, static_cast<u64>(j));
      auto const result = [x](u64 y) {
        u64 ret = 1;
        for (u64 i = 1; i <= y; ++i)
        {
          ret *= x;
        }
        return static_cast<value_type>(ret);
      }(static_cast<u64>(j));

      TestFixture::equal(v, result);
    },
    0,
    11,
    0,
    11);
}

REGISTER_TYPED_TEST_CASE_P(math_utility_test, abs, mod, factorial, power);
using test_case = ::testing::Types<int, unsigned int, float, double>;
INSTANTIATE_TYPED_TEST_CASE_P(need_integer_test, math_utility_test, test_case);
} // namespace need_integer_test
