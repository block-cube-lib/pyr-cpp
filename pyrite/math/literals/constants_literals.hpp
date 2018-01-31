/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_CONSTANTS_LITERALS_HPP
#define PYRITE_MATH_CONSTANTS_LITERALS_HPP

#include <pyrite/math/constants.hpp>

namespace pyrite::math::literals
{
/**********************
 * pi literals
 **********************/
constexpr double operator"" _pi(long double value)
{
  return static_cast<double>(value * ::pyrite::math::pi<long double>);
}

constexpr float operator"" _pif(long double value)
{
  return static_cast<float>(value * ::pyrite::math::pi<long double>);
}

constexpr long double operator"" _pil(long double value)
{
  return value * ::pyrite::math::pi<long double>;
}

constexpr double operator"" _pi(unsigned long long value)
{
  return static_cast<double>(value * ::pyrite::math::pi<long double>);
}

constexpr float operator"" _pif(unsigned long long value)
{
  return static_cast<float>(value * ::pyrite::math::pi<long double>);
}

constexpr long double operator"" _pil(unsigned long long value)
{
  return value * ::pyrite::math::pi<long double>;
}
} // namespace pyrite::math::literals

#endif // PYRITE_MATH_CONSTANTS_LITERALS_HPP
