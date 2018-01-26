/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_UTILITY_HPP
#define PYRITE_MATH_UTILITY_HPP

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

} // namespace pyrite::math
#endif // PYRITE_MATH_UTILITY_HPP
