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
using i8  = core::i8;  //!< 8 bit signed integer type.
using i16 = core::i16; //!< 16 bit signed integer type.
using i32 = core::i32; //!< 32 bit signed integer type.
using i64 = core::i64; //!< 64 bit signed integer type.

using u8  = core::u8;  //!< 8 bit unsigned integer type.
using u16 = core::u16; //!< 16 bit unsigned integer type.
using u32 = core::u32; //!< 32 bit unsigned integer type.
using u64 = core::u64; //!< 64 bit unsigned integer type.

using f32 = core::f32; //!< 32 bit floating point type.
using f64 = core::f64; //!< 64 bit floating point type.

using isize =
  core::isize; //!< Signed intger type large enough to represent size.
using usize =
  core::usize; //!< Unsigned intger type large enough to represent size.

using byte = u8; // 8 bit unsigned integer type.

using iptr = core::iptr; // Signed integer type capable of holding a pointer.
using uptr = core::uptr; // Unsigned integer type capable of holding a pointer.
using ptrdiff = core::ptrdiff; // Result of subtracting two pointers.
} // namespace pyrite

#endif // PYRITE_CORE_TYPE_HPP
