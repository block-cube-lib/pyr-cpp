/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_VECTOR_VECTOR_HPP
#define PYRITE_MATH_VECTOR_VECTOR_HPP

#include <array>
#include <initializer_list>
#include <type_traits>
#include <utility>

#include <pyrite/core/type.hpp>
#include <pyrite/math/utility.hpp>
#include <pyrite/math/vector/vector_fwd.hpp>
#include <pyrite/mpl/type_list.hpp>

namespace pyrite::math
{
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
  using value_type = T;

  /****************************************************************************
   * static constexpr value
   ****************************************************************************/
  static constexpr usize dimension = dimension;

  /****************************************************************************
   * constructor
   ****************************************************************************/
  constexpr vector() noexcept = default;
  constexpr vector(vector const& other) noexcept : vector(other.elements) {}
  constexpr vector(vector&& other) noexcept : vector(std::move(other.elements))
  {
  }
  constexpr vector(T const (&v)[Dimension])
    : vector(v, std::make_index_sequence<Dimension>{})
  {
  }
  constexpr vector(std::initializer_list<T> const& list)
    : vector(list, std::make_index_sequence<Dimension>{})
  {
  }

  /****************************************************************************
   * member function
   ****************************************************************************/
  constexpr T length() const;
  constexpr T length_squared() const;

  constexpr T normalize();
  constexpr T normalized() const;

  constexpr T distance(vector const& other) const;
  constexpr T dot(vector const& other) const;

  /****************************************************************************
   * operator
   ****************************************************************************/
  constexpr T&       operator[](usize index) { return elements[index]; }
  constexpr T const& operator[](usize index) const { return elements[index]; }

  constexpr vector& operator=(vector const& other)
  {
    for (usize i = 0; i < Dimension; ++i)
    {
      elements[i] = other.elements[i];
    }
    return *this;
  }
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
  template <std::size_t... Index>
  constexpr vector(T const (&v)[Dimension], std::index_sequence<Index...>)
    : elements{v[Index]...}
  {
  }

  template <std::size_t... Index>
  constexpr vector(T const(&&v)[Dimension], std::index_sequence<Index...>)
    : elements{std::move(v[Index])...}
  {
  }

  template <std::size_t... Index>
  constexpr vector(std::initializer_list<T> const& list,
                   std::index_sequence<Index...>)
    : elements{get_initializer_list_element(list, Index)...}
  {
  }

  static constexpr T
    get_initializer_list_element(std::initializer_list<T> const& list,
                                 std::size_t                     index)
  {
    return index < list.size() ? (*(list.begin() + index)) : T{0};
  }

public:
  /****************************************************************************
   * member variable
   ****************************************************************************/
  T elements[Dimension] = {}; //!< elements
};
} // namespace pyrite::math

#endif // PYRITE_MATH_VECTOR_VECTOR_HPP
