/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_CORE_TYPE_HPP
#define PYRITE_CORE_TYPE_HPP

#if defined(CHAR_BIT)
static_assert(CHAR_BIT == 8, "not support.");
#endif

#include <pyrite/core/detail/type.hpp>

namespace pyrite
{
using i8  = detail::i8;  //!< 8 bit signed integer type.
using i16 = detail::i16; //!< 16 bit signed integer type.
using i32 = detail::i32; //!< 32 bit signed integer type.
using i64 = detail::i64; //!< 64 bit signed integer type.

using u8  = detail::u8;  //!< 8 bit unsigned integer type.
using u16 = detail::u16; //!< 16 bit unsigned integer type.
using u32 = detail::u32; //!< 32 bit unsigned integer type.
using u64 = detail::u64; //!< 64 bit unsigned integer type.

using f32 = detail::f32; //!< 32 bit floating point type.
using f64 = detail::f64; //!< 64 bit floating point type.

using isize =
  detail::isize; //!< Signed intger type large enough to represent size.
using usize =
  detail::usize; //!< Unsigned intger type large enough to represent size.

using byte = u8; // 8 bit unsigned integer type.

using ipointer     = isize; // Signed integer type capable of holding a pointer.
using upointer     = usize; // Unsigned integer type capable of holding a pointer.
using pointer_diff = isize;
} // namespace pyrite

#endif // PYRITE_CORE_TYPE_HPP
