/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_VECTOR_TRAITS_ARRAY_HPP
#define PYRITE_MATH_VECTOR_TRAITS_ARRAY_HPP

#include <array>
#include <pyrite/math/vector_traits.hpp>

namespace pyrite
{
namespace math
{
/**
 * Traits for abstract access to vector type.
 * Specialization for std::array<T, N>.
 */
template <typename T, std::size_t N>
struct vector_traits<std::array<T, N>>
{
  /**
   * The type of vector.
   */
  using vector_type = std::array<T, N>;

  /**
   * Element type of vector.
   */
  using value_type = T;

  /**
   * Dimension of vector.
   */
  static constexpr usize dimension = N;

  /**
   * Access to elements of editable vector.
   * @param[in] vector vector
   * @param[in] index Index of vector.
   * @return A reference to an element of an editable vector.
   */
  static constexpr value_type& at(vector_type& vector, usize const& index)
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
    at(vector_type const& vector, usize const& index)
  {
    return vector[index];
  }
}; // vector_traits

/**
 * Traits for abstract access to vector type.
 * Specialization for embedded array.
 */
template <typename T, std::size_t N>
struct vector_traits<T[N]>
{
  /**
   * The type of vector.
   */
  using vector_type = T[N];

  /**
   * Element type of vector.
   */
  using value_type = T;

  /**
   * Dimension of vector.
   */
  static constexpr usize dimension = N;

  /**
   * Access to elements of editable vector.
   * @param[in] vector vector
   * @param[in] index Index of vector.
   * @return A reference to an element of an editable vector.
   */
  static constexpr value_type& at(vector_type& vector, usize const& index)
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
    at(vector_type const& vector, usize const& index)
  {
    return vector[index];
  }
}; // vector_traits
} // namespace math
} // namespace pyrite

#endif // PYRITE_MATH_VECTOR_TRAITS_ARRAY_HPP
