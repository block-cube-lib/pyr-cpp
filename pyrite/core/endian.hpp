/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_CORE_ENDIAN_HPP
#define PYRITE_CORE_ENDIAN_HPP

#include <pyrite/core/type.hpp>

namespace pyrite
{
inline namespace core
{
/**
 * An enumerated type representing the order of bytes (endian).
 */
enum class endian : i8
{
  /** Big endian. */
  big,
  /** Little endian. */
  little,

  /** Endian of execution environment. big or little */
  native =
#if __BIG_ENDIAN__
    big
#elif __LITTLE_ENDIAN__
    little
#elif defined(__BYTE_ORDER__)
#  if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    big
#  elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    little
#  endif
#endif
};
} // namespace core
} // namespace pyrite

#endif // PYRITE_CORE_ENDIAN_HPP
