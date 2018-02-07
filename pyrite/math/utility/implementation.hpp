/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_UTILITY_IMPLEMENTATION_HPP
#define PYRITE_MATH_UTILITY_IMPLEMENTATION_HPP

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

#include <pyrite/core/type.hpp>
#include <pyrite/math/constants.hpp>

namespace pyrite::math
{
namespace detail
{
template <typename T>
using calc_t =
  std::conditional_t<std::is_integral_v<T>, std::intmax_t, long double>;
}
template <typename T>
constexpr auto radian_to_degree(T const& radian) noexcept
{
  using result_t = std::conditional_t<std::is_floating_point_v<T>, T, double>;
  return radian * result_t{180} / pi<result_t>;
}

template <typename T>
constexpr auto degree_to_radian(T const& degree) noexcept
{
  using result_t = std::conditional_t<std::is_floating_point_v<T>, T, double>;
  return degree * pi<result_t> / result_t{180};
}

template <typename T>
constexpr T abs(T value) noexcept
{
  if constexpr (std::is_signed<T>::value)
  {
    return value >= 0 ? value : -value;
  }
  else
  {
    return value;
  }
}

template <typename T>
constexpr T mod(T x, T y)
{
  if constexpr (std::is_floating_point_v<T>)
  {
    return x - static_cast<std::intmax_t>(x / y) * y;
  }
  else
  {
    return x % y;
  }
}

template <typename T>
constexpr T factorial(u64 x)
{
  assert(0 <= x);
  if constexpr (std::is_integral_v<T>)
  {
    assert(x < 21u); // overflow
  }

  detail::calc_t<T> result{1};
  for (u64 i = 1u; i <= x; ++i)
  {
    result *= static_cast<detail::calc_t<T>>(i);
  }

  return static_cast<T>(result);
}

template <typename T>
constexpr T power(T x, u64 y)
{
  detail::calc_t<T> result{1};

  for (u64 i = 1; i <= y; ++i)
  {
    result *= x;
  }

  return result;
}

template <typename T>
constexpr bool isnan(T value)
{
  static_assert(std::is_floating_point_v<T>);
  return value == std::numeric_limits<T>::quiet_NaN() ||
         value == std::numeric_limits<T>::signaling_NaN();
}

template <typename T>
constexpr bool is_infinity(T value)
{
  static_assert(std::is_floating_point_v<T>);
  return value == std::numeric_limits<T>::infinity() ||
         value == std::numeric_limits<T>::infinity();
}

template <typename T>
constexpr bool equal(T lhs, T rhs)
{
  if constexpr (std::is_floating_point_v<T>)
  {
    if (isnan(lhs) || isnan(rhs))
    {
      return false;
    }
    else if (is_infinity(lhs) && is_infinity(rhs))
    {
      return true;
    }
    else
    {
      constexpr auto epsilon = (std::is_same_v<T, long double> ? 1000 : 10) *
                               std::numeric_limits<T>::epsilon();
      auto const max = std::max(abs(rhs), abs(lhs));
      return abs(lhs - rhs) <= epsilon || abs(lhs - rhs) <= max * epsilon;
    }
  }
  else
  {
    return lhs == rhs;
  }
}

template <typename T>
constexpr auto sqrt(T s)
{
  using calc_t   = long double;
  using result_t = std::conditional_t<std::is_floating_point_v<T>, T, double>;

  constexpr result_t zero{0};
  assert(zero <= s);
  if (equal(s, zero))
  {
    return zero;
  }

  calc_t x    = s / 2;
  calc_t prev = 0;

  constexpr int end_term = 100;
  for (int i = 0; i < end_term && !equal(x, prev); ++i)
  {
    prev = x;
    x    = (x + s / x) / 2;
  }

  return static_cast<result_t>(x);
}

namespace detail
{
constexpr u64 end_term = 10;

template <typename T>
constexpr T sin_term(T x)
{
  T sum{0};
  for (u64 k = 0; k <= end_term; ++k)
  {
    int const sign = (k == 0 || k % 2 == 0) ? 1 : -1;
    sum += sign * power(x, 2 * k + 1) / factorial<T>(2 * k + 1);
  }
  return sum;
}

template <typename T>
constexpr T sin_convert(T x)
{
  assert(-pi<T> <= x && x <= pi<T>);

  if (abs(x) > pi<T> / 2) // x < -pi/2 || pi/2 < x
  {
    return sin_term(mod(pi<T> - x, pi<T>) * static_cast<int>(x * 2 / pi<T>));
  }
  else
  {
    return sin_term(x);
  }
}
} // namespace detail

template <typename T>
constexpr T sin(T x)
{
  static_assert(std::is_floating_point_v<T>);
  auto const sign = static_cast<int>(x / pi<T>) % 2 == 0 ? 1 : -1;
  x               = mod(x, pi<T>); // -pi < x < pi
  return sign *
         static_cast<T>(detail::sin_convert(static_cast<long double>(x)));
}

template <typename T>
constexpr auto cos(T x)
{
  static_assert(std::is_floating_point_v<T>);
  constexpr auto pi_half = pi<T> / 2;
  return equal(abs(mod(x, 2 * pi<T>)), pi_half) ? 0 : sin(x + pi_half);
}

template <typename T>
constexpr auto sincos(T x)
{
  using calc_t = long double;

  static_assert(std::is_floating_point_v<T>);
  x = mod(x, 2 * pi<T>);
  if (x < 0)
  {
    x = 2 * pi<T> - -x;
  }

  auto const s = pyrite::math::sin(static_cast<calc_t>(x));

  constexpr auto pi_half = pi<T> / 2;
  if (equal(x, pi_half) || equal(x, pi_half * 3))
  {
    return std::pair<T, T>{static_cast<T>(s), 0};
  }
  else
  {
    auto const sign = (x <= pi_half || pi_half * 3 < x) ? 1 : -1;
    auto const c    = sign * sqrt(1 - s * s);
    return std::pair<T, T>{static_cast<T>(s), static_cast<T>(c)};
  }
}

template <typename T>
constexpr auto tan(T x)
{
  auto const [sin, cos] = sincos(static_cast<long double>(x));
  return static_cast<T>(sin / cos);
}

namespace detail
{
constexpr long double asin_term_sum(long double x)
{
  auto const term = [x](u64 n) {
    auto const k = 2u * n + 1u;
    return (power(x, k) * factorial<long double>(2u * n)) /
           (power(4u, n) * power(factorial<long double>(n), 2u) * k);
  };

  long double result{0};
  for (u64 i = 0; i <= 13; ++i)
  {
    result += term(i);
  }

  return result;
}

constexpr long double asin(long double x)
{
  assert(abs(x) <= 1.0l);

  constexpr long double sqrt2{sqrt(2.0l)};
  if (1.0l / sqrt2 < abs(x) && abs(x) <= 1.0l)
  {
    auto const result =
      pi<long double> / 2 - asin_term_sum(sqrt(1.0l - power(x, 2.0l)));
    return 0.0l <= x ? result : -result;
  }
  else
  {
    return asin_term_sum(x);
  }
}

} // namespace detail

template <typename T>
constexpr auto asin(T x)
{
  using result_t = std::conditional_t<std::is_floating_point_v<T>, T, double>;
  return static_cast<result_t>(detail::asin(static_cast<long double>(x)));
}

} // namespace pyrite::math

#endif // PYRITE_MATH_UTILITY_IMPLEMENTATION_HPP
