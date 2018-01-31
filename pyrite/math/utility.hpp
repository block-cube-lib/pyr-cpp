/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_UTILITY_HPP
#define PYRITE_MATH_UTILITY_HPP

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

/**
 * Convert Radian to Degree.
 *
 * @tparam T      Degree type.
 * @param  radian Radian.
 * @return Degree.
 */
template <typename T>
constexpr T radian_to_degree(T const& radian) noexcept
{
  using result_t = std::conditional_t<std::is_floating_point_v<T>, T, double>;
  return radian * result_t{180} / pi<result_t>;
}

/**
 * Convert Degree to Radian.
 *
 * @tparam T      Radian type.
 * @param  degree Degree.
 * @return Radian.
 */
template <typename T>
constexpr auto degree_to_radian(T const& degree) noexcept
{
  using result_t = std::conditional_t<std::is_floating_point_v<T>, T, double>;
  return degree * pi<result_t> / result_t{180};
}

/**
 * Computes the absolute value.
 *
 * @tparam T type.
 * @param value value.
 * @return Absolute value.
 */
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

template <typename T = u64>
constexpr T factorial(u64 x)
{
  assert(0 <= x);
  assert(x < 21u); // overflow
  u64 result{1};
  for (u64 i = 1u; i <= x; ++i)
  {
    auto const new_value = result * i;
    assert(result <= new_value);
    result = new_value;
  }

  return static_cast<T>(result);
}

template <typename T>
constexpr T power(T x, u64 y)
{
  T result{1};

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
  using result_t = std::conditional_t<std::is_floating_point_v<T>, T, double>;

  constexpr result_t zero{0};
  if (equal(s, zero))
  {
    return zero;
  }

  assert(zero <= s);
  constexpr int end_term = 100;
  result_t      x        = s / 2;
  result_t      prev     = 0;
  for (int i = 0; i < end_term && !equal(x, prev); ++i)
  {
    prev = x;
    x    = (x + s / x) / 2;
  }

  return x;
}

namespace detail
{
constexpr u64 end_term = 9;

template <typename T>
constexpr T sin_term(T x)
{
  T sum{0};
  for (u64 k = 0; k <= end_term; ++k)
  {
    int const sign = (k == 0 || k % 2 == 0) ? 1 : -1;
    sum += sign * power(x, 2 * k + 1) / factorial(2 * k + 1);
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
  return sign * detail::sin_convert(x);
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
  static_assert(std::is_floating_point_v<T>);
  x = mod(x, 2 * pi<T>);
  if (x < 0)
  {
    x = 2 * pi<T> - -x;
  }

  auto const s = pyrite::math::sin(x);

  constexpr auto pi_half = pi<T> / 2;
  if (equal(x, pi_half) || equal(x, pi_half * 3))
  {
    return std::pair<T, T>{s, 0};
  }
  else
  {
    auto const sign = (x <= pi_half || pi_half * 3 < x) ? 1 : -1;
    auto const c    = sign * sqrt(1 - s * s);
    return std::pair<T, T>{s, c};
  }
}

template <typename T>
constexpr auto tan(T x)
{
  auto const [sin, cos] = sincos(x);
  return sin / cos;
}

} // namespace pyrite::math
#endif // PYRITE_MATH_UTILITY_HPP
