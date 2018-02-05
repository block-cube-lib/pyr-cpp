/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_VECTOR_VECTOR2_HPP
#define PYRITE_MATH_VECTOR_VECTOR2_HPP

#include <array>
#include <initializer_list>
#include <type_traits>

#include <pyrite/core/type.hpp>
#include <pyrite/math/utility.hpp>
#include <pyrite/math/vector/vector_fwd.hpp>

namespace pyrite::math
{
template <typename T>
class vector<T, 2>
{
public:
  static_assert(std::is_floating_point_v<T>);

  using value_type                 = T;
  static constexpr usize dimension = dimension;

  constexpr vector() noexcept = default;
  constexpr vector(T x, T y) noexcept : x(x), y(y) {}
  constexpr vector(vector const& other) noexcept = default;
  constexpr vector(T const (&v)[2]) {}
  constexpr vector(std::initializer_list<T> const& ilist) {}

  /****************************************************************************
   * member function
   ****************************************************************************/
  constexpr T dot(vector const& other) const { return dot(*this); }
  constexpr T cross(vector const& other) const;

  constexpr T distance(vector const& other) const
  {
    return distance(*this, other);
  }

  constexpr T distance_sqared(vector const& other) const
  {
    return distance_sqared(*this, other);
  }

  constexpr T length() const { return length(*this); }
  constexpr T length_squared() const { return length_squared(*this); }

  constexpr vector& normalize() { return normalize(*this); }
  constexpr vector  normalized() const { return normalized(*this); }

  constexpr T& operator[](usize index)
  {
    assert(0 <= index && index <= 1);
    return index == 0 ? x : y;
  }

  constexpr T const& operator[](usize index) const
  {
    assert(0 <= index && index <= 1);
    return index == 0 ? x : y;
  }

  constexpr vector& operator=(vector const& other)
  {
    x = other.x;
    y = other.y;
    return *this;
  }

  constexpr vector& operator=(vector&& other)
  {
    x = std::move(other.x);
    y = std::move(other.y);
    return *this;
  }

public:
  T x = T{0};
  T y = T{0};
};
} // namespace pyrite::math

#endif // PYRITE_MATH_VECTOR_VECTOR2_HPP
