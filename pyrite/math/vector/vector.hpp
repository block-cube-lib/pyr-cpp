/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_VECTOR_VECTOR_HPP
#define PYRITE_MATH_VECTOR_VECTOR_HPP

#include <initializer_list>
#include <type_traits>
#include <utility>

#include <pyrite/core/type.hpp>
#include <pyrite/math/vector/utility_fwd.hpp>
#include <pyrite/math/vector/vector_fwd.hpp>

namespace pyrite::math
{
/**
 * vector
 *
 * @tparam T         type of vector element.
 * @tparam Dimension dimension of vector.
 */
template <typename T, usize Dimension>
class vector
{
public:
  /****************************************************************************
   * assertion
   ****************************************************************************/
  static_assert(0 < Dimension);
  static_assert(std::is_floating_point_v<T>);

  /****************************************************************************
   * type alias
   ****************************************************************************/
  using value_type = T; //!< type of vector element.

  /****************************************************************************
   * static constexpr value
   ****************************************************************************/
  static constexpr usize dimension = dimension; //!< dimension of vector

  /****************************************************************************
   * constructor
   ****************************************************************************/
  /**
   * initialize all elements to zero.
   */
  constexpr vector() noexcept = default;

  /**
   * copy constructor.
   * @param other source
   */
  constexpr vector(vector const& other) noexcept : vector(other.elements) {}

  /**
   * move constructor.
   * @param other source
   */
  constexpr vector(vector&& other) noexcept : vector(std::move(other.elements))
  {
  }

  /**
   * initialize from array.
   * @param v array
   */
  constexpr vector(T const (&v)[Dimension])
    : vector(v, std::make_index_sequence<Dimension>{})
  {
  }

  /**
   * initialize from std::initializer_list.
   * @param other source
   */
  constexpr vector(std::initializer_list<T> const& ilist)
    : vector(ilist, std::make_index_sequence<Dimension>{})
  {
  }

  /**
   */
  template <typename U>
  constexpr explicit vector(vector<U, Dimension> const& other)
    : vector(other, std::make_index_sequence<Dimension>{})
  {
  }

  /****************************************************************************
   * member function
   ****************************************************************************/
  constexpr T dot(vector const& other) const { return dot(*this, other); }

  constexpr T distance(vector const& other) const
  {
    return distance(*this, other);
  }

  constexpr T distance_squared(vector const& other) const
  {
    return distance_squared(*this, other);
  }

  constexpr T length() const { return length(*this); }

  constexpr T length_squared() const { return length_squared(*this); }

  constexpr vector& normalize() { return normalize(*this); }

  constexpr vector normalized() const { return normalized(*this); }

  /****************************************************************************
   * operator
   ****************************************************************************/
  /**
   * access specified element.
   *
   * @param  index index of the element to return.
   * @return reference to the requested element.
   */
  constexpr T& operator[](usize index) { return elements[index]; }

  /**
   * access specified element.
   *
   * @param  index index of the element to return.
   * @return const reference to the requested element.
   */
  constexpr T const& operator[](usize index) const { return elements[index]; }

  /**
   * copy assignment operator.
   *
   * @param other source.
   * @return *this
   */
  constexpr vector& operator=(vector const& other)
  {
    for (usize i = 0; i < Dimension; ++i)
    {
      elements[i] = other.elements[i];
    }
    return *this;
  }

  /**
   * move assignment operator.
   *
   * @param other source.
   * @return *this
   */
  constexpr vector& operator=(vector&& other)
  {
    for (usize i = 0; i < Dimension; ++i)
    {
      elements[i] = std::move(other.elements[i]);
    }
    return *this;
  }

private:
  /****************************************************************************
   * private constructor
   ****************************************************************************/
  /**
   * construct from array
   */
  template <std::size_t... Index>
  constexpr vector(T const (&v)[Dimension], std::index_sequence<Index...>)
    : elements{v[Index]...}
  {
  }

  /**
   * move from array
   */
  template <std::size_t... Index>
  constexpr vector(T const(&&v)[Dimension], std::index_sequence<Index...>)
    : elements{std::move(v[Index])...}
  {
  }

  /**
   * construct from std::initializer_list
   */
  template <std::size_t... Index>
  constexpr vector(std::initializer_list<T> const& ilist,
                   std::index_sequence<Index...>)
    : elements{get_initializer_list_element(ilist, Index)...}
  {
  }

  static constexpr T
    get_initializer_list_element(std::initializer_list<T> const& ilist,
                                 std::size_t                     index)
  {
    return index < ilist.size() ? (*(ilist.begin() + index)) : T{0};
  }

  /**
   * construct from another type vector
   */
  template <typename U, std::size_t... Index>
  constexpr vector(vector<U, Dimension> const& other,
                   std::index_sequence<Index...>)
    : elements{static_cast<T>(other.elements[Index])...}
  {
  }

public:
  /****************************************************************************
   * member variable
   ****************************************************************************/
  T elements[Dimension] = {}; //!< elements
};
} // namespace pyrite::math

#  include <pyrite/math/vector/utility.hpp>

#endif // PYRITE_MATH_VECTOR_VECTOR_HPP
