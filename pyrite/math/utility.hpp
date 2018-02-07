/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_UTILITY_HPP
#define PYRITE_MATH_UTILITY_HPP

#include <pyrite/core/type.hpp>

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
constexpr auto radian_to_degree(T const& radian) noexcept;

/**
 * Convert Degree to Radian.
 *
 * @tparam T      Radian type.
 * @param  degree Degree.
 * @return Radian.
 */
template <typename T>
constexpr auto degree_to_radian(T const& degree) noexcept;

/**
 * Computes the absolute value.
 *
 * @tparam T type.
 * @param value value.
 * @return Absolute value.
 */
template <typename T>
constexpr T abs(T value) noexcept;

template <typename T>
constexpr T mod(T x, T y);

template <typename T = u64>
constexpr T factorial(u64 x);

template <typename T>
constexpr T power(T x, u64 y);

template <typename T>
constexpr bool isnan(T value);

template <typename T>
constexpr bool is_infinity(T value);

template <typename T>
constexpr bool equal(T lhs, T rhs);

template <typename T>
constexpr auto sqrt(T s);

template <typename T>
constexpr T sin(T x);

template <typename T>
constexpr auto cos(T x);

template <typename T>
constexpr auto sincos(T x);

template <typename T>
constexpr auto tan(T x);

template <typename T>
constexpr auto asin(T x);
} // namespace pyrite::math

#  include <pyrite/math/utility/implementation.hpp>

#endif // PYRITE_MATH_UTILITY_HPP
