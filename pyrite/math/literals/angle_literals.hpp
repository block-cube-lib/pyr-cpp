/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_LITERALS_ANGLE_LITERALS_HPP
#define PYRITE_MATH_LITERALS_ANGLE_LITERALS_HPP

#include <pyrite/math/angle.hpp>

namespace pyrite::math::literals
{
#define DEF_LITERAL(TYPE, LITERAL, TAG)                                        \
  constexpr angle<TYPE> operator"" LITERAL(long double v)                      \
  {                                                                            \
    return angle<TYPE>{v, TAG};                                                \
  }                                                                            \
                                                                               \
  constexpr angle<TYPE> operator"" LITERAL(unsigned long long v)               \
  {                                                                            \
    return angle<TYPE>{static_cast<TYPE>(v), TAG};                             \
  }

DEF_LITERAL(float, _radf, ::pyrite::math::radian_tag);
DEF_LITERAL(double, _rad, ::pyrite::math::radian_tag);
DEF_LITERAL(long double, _radl, ::pyrite::math::radian_tag);

DEF_LITERAL(float, _degf, ::pyrite::math::degree_tag);
DEF_LITERAL(double, _deg, ::pyrite::math::degree_tag);
DEF_LITERAL(long double, _degl, ::pyrite::math::degree_tag);

#undef DEF_LITERAL

#define PI_RAD_LITERAL(TYPE, LITERAL)                                          \
  constexpr angle<TYPE> operator"" LITERAL(long double v)                      \
  {                                                                            \
    using namespace pyrite::math;                                            \
    return angle<TYPE>{v * pi<TYPE>, radian_tag};                              \
  }                                                                            \
                                                                               \
  constexpr angle<TYPE> operator"" LITERAL(unsigned long long v)               \
  {                                                                            \
    using namespace pyrite::math;                                            \
    return angle<TYPE>{static_cast<TYPE>(v) * pi<TYPE>, radian_tag};           \
  }

PI_RAD_LITERAL(float, _pi_radf);
PI_RAD_LITERAL(double, _pi_rad);
PI_RAD_LITERAL(long double, _pi_radl);

#undef PI_RAD_LITERAL
} // namespace pyrite::math::literals

#endif // PYRITE_MATH_LITERALS_ANGLE_LITERALS_HPP
