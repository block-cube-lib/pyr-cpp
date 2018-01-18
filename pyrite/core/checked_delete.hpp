/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_CHECKED_DELETE_HPP
#define PYRITE_CHECKED_DELETE_HPP

#include <pyrite/core/is_complete_type.hpp>

namespace pyrite
{
namespace core
{
/**
 * After deleting the pointer, assing nullptr.
 * @tparam T T must be a complete type.
 * @param ptr pointer.
 */
template <typename T>
void checked_delete(T*& ptr)
{
  static_assert(is_complete_type<T>::value, "type T is not a complete type.");

  delete ptr;
  ptr = nullptr;
}

/**
 * After deleting the pointer, assing nullptr.
 * Array version of checked_delete.
 * @tparam T T must be a complete type.
 * @param ptr pointer.
 */
template <typename T>
void checked_array_delete(T*& ptr)
{
  static_assert(is_complete_type<T>::value, "type T is not a complete type.");

  delete[] ptr;
  ptr = nullptr;
}

/**
 * A function object thet calls checked_delete with operator().
 * @tparam T Must be a complete type.
 */
template <typename T>
class checked_deleter
{
public:
  using result_type   = void; ///< The result type of the operator().
  using argument_type = T*&;  ///< The argument type of the operator().

  /**
   * Call checked_delete.
   * @param ptr pointer.
   */
  void operator()(T*& ptr) const { checked_delete(ptr); }
};

/**
 * A function object thet calls checked_delete with operator().
 * @tparam T Must be a complete type.
 */
template <typename T>
class checked_array_deleter
{
public:
  using result_type   = void; ///< The result type of the operator().
  using argument_type = T*&;  ///< The argument type of the operator().

  /**
   * Call checked_array_delete.
   * @param ptr pointer.
   */
  void operator()(T*& ptr) const { checked_array_delete(ptr); }
};
} // namespace core

using core::checked_array_delete;
using core::checked_array_deleter;
using core::checked_delete;
using core::checked_deleter;
} // namespace pyrite

#endif // PYRITE_CHECKED_DELETE_HPP
