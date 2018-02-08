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

/**
 * Computes the reminder of the division operation 'x/y'.
 *
 * @tparam T arguments and result type.
 * @param x left hand side.
 * @param y right hand side.
 * @return if T is integer type then returns x%y,
 *         and if T is floating point type then returns x - (int)(x/y).
 */
template <typename T>
constexpr T mod(T x, T y);

/**
 * Computes the factorial of x.
 *
 * @tparam T result type.
 * @param x value.
 * @return x!.
 */
template <typename T = u64>
constexpr T factorial(u64 x);

/**
 * Computes the value of x raised to the power y.
 *
 * @tparam T result type.
 * @param x base.
 * @param y integer exp.
 * @return x^y
 */
template <typename T>
constexpr T power(T x, u64 y);

/**
 * return true when if the value is NaN.
 *
 * @tparam T floating point type.
 * @param floating point value.
 * @return value == NaN.
 */
template <typename T>
constexpr bool isnan(T value);

/**
 * returns true when if the value is infinity.
 *
 * @tparam T floating point type.
 * @param floating point value.
 * @return value == infinity.
 */
template <typename T>
constexpr bool is_infinity(T value);

/**
 * returns true if the lhs (near) equal to the rhs.
 * returns the lhs near equal to the rhs if T is a floating point type,
 * and lhs == rhs otherwise.
 *
 * @tparam T value type.
 * @param lhs
 * @param rhs
 * @return the lhs equal to the rhs.
 */
template <typename T>
constexpr bool equal(T lhs, T rhs);

/**
 * Computes the square root of argument.
 *
 * @tparam T argument type.
 * @tparam s vlaue of a floating point or integer type.
 * @return if T is an integer type then returns double type value,
 *         and if T is a floating point type then returns T type value.
 */
template <typename T>
constexpr auto sqrt(T s);

/**
 * Computes sine of argument.
 *
 * @tparam T argument and result type.
 * @param x radian.
 * @return sine of argument.
 */
template <typename T>
constexpr T sin(T x);

/**
 * Computes cosine of argument.
 *
 * @tparam T argument and result type.
 * @param x radian.
 * @return sine of argument.
 */
template <typename T>
constexpr auto cos(T x);

/**
 * Computes sine and cosine of argument.
 *
 * @tparam T argument and result type.
 * @param x radian.
 * @return pair<T, T>{sin, cos}.
 */
template <typename T>
constexpr auto sincos(T x);

/**
 * Computes tangent of argument.
 *
 * @tparam T argument and result type.
 * @param x radian.
 * @return tangent of argument.
 */
template <typename T>
constexpr auto tan(T x);

/**
 * Computes arc sine of argument.
 *
 * @tparam T argument and result type.
 * @param x radian.
 * @return arc sine of argument.
 */
template <typename T>
constexpr auto asin(T x);
} // namespace pyrite::math

#  include <pyrite/math/utility/implementation.hpp>

#endif // PYRITE_MATH_UTILITY_HPP
