/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_MATH_VECTOR_TRAITS_HPP
#define PYRITE_MATH_VECTOR_TRAITS_HPP

#include <pyrite/config/type.hpp>
#include <pyrite/core/integral_constant.hpp>

namespace pyrite
{
namespace math
{
/**
 * Traits for abstract access to vector type.
 */
template <typename T>
struct vector_traits
{
  /**
   * The type of vector.
   */
  using vector_type = T;

  /**
   * Element type of vector.
   */
  using value_type = typename T::value_type;

  /**
   * Dimension of vector.
   */
  static constexpr usize dimension = T::dimension;

  /**
   * Access to elements of editable vector.
   * @param[in] vector vector
   * @param[in] index Index of vector.
   * @return A reference to an element of an editable vector.
   */
  static constexpr value_type& at( vector_type& vector, usize const& index )
  {
    return vector[index];
  }

  /**
   * Access to elements of uneditable vector.
   * @param[in] vector vector
   * @param[in] index Index of vector.
   * @return A reference to an element of an uneditable vector.
   */
  static constexpr value_type const&
    at( vector_type const& vector, usize const& index )
  {
    return vector[index];
  }
}; // vector_traits
} // namespace math
} // namespace pyrite

#endif // PYRITE_MATH_VECTOR_TRAITS_HPP
