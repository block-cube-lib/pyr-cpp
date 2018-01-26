/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_UTILITY_HPP
#define PYRITE_MATH_UTILITY_HPP

#include <cassert>
#include <cstdint>
#include <type_traits>

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
  return radian * T{180} / pi<T>;
}

/**
 * Convert Degree to Radian.
 *
 * @tparam T      Radian type.
 * @param  degree Degree.
 * @return Radian.
 */
template <typename T>
constexpr T degree_to_radian(T const& degree) noexcept
{
  return degree * pi<T> / T{180};
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

template <typename T = std::uintmax_t>
T factorial(std::uintmax_t x)
{
  std::uintmax_t result{1};
  for (std::uintmax_t i = 1; i <= x; ++i)
  {
    auto const new_value = result * i;
    assert(result <= new_value);
    result = new_value;
  }

  return static_cast<T>(result);
}

template <typename T>
constexpr T power(T x, std::uintmax_t y)
{
  T result{1};

  for (std::uintmax_t i = 1; i <= y; ++i)
  {
    result *= x;
  }

  return result;
}

namespace detail
{
constexpr std::uintmax_t end_term = 10;

template <typename T>
constexpr T sin_term_sum(T x)
{
  auto const term = [x](std::uintmax_t k) constexpr
  {
    int const t = (k == 0 || k % 2 == 0) ? 1 : -1;
    return t * power(x, 2 * k + 1) / factorial(2 * k + 1);
  };

  T sum{0};
  for (std::uintmax_t i = 0; i <= end_term; ++i)
  {
    sum += term(i);
  }
  return sum;
}

template <typename T>
constexpr T sin_convert(T x)
{
  assert(-pi<T> <= x && x <= pi<T>);

  if (abs(x) > pi<T> / 2) // x < -pi/2 || pi/2 < x
  {
    return sin_term_sum(mod(pi<T> - x, pi<T>) *
                 static_cast<int>(x * 2 / pi<T>));
  }
  else
  {
    return sin_term_sum(x);
  }
}
} // namespace detail

template <typename T>
constexpr auto sin(T x)
  -> std::conditional_t<std::is_floating_point_v<T>, T, double>
{
  auto const sign = static_cast<int>(x / pi<T>) % 2 == 0 ? 1 : -1;
  x               = mod(x, pi<T>); // -pi < x < pi
  return sign * detail::sin_convert(x);
}

} // namespace pyrite::math
#endif // PYRITE_MATH_UTILITY_HPP
