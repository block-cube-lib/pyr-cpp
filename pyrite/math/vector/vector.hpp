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
  static_assert(0 < Dimension);
  static_assert(std::is_floating_point_v<T>);

  using value_type                 = T;
  static constexpr usize dimension = dimension;

  constexpr vector() noexcept                    = default;
  constexpr vector(vector const& other) noexcept = default;
  template <typename... Args>
  constexpr vector(Args&&... args) : elements{{static_cast<T>(std::forward<Args>(args))...}}
  {
    using list = mpl::type_list<Args...>;
    static_assert(list::size == Dimension);
  }

  constexpr T length() const;
  constexpr T length_squared() const;

  constexpr T normalize();
  constexpr T normalized() const;

  constexpr T distance(vector const& other) const;
  constexpr T dot(vector const& other) const;

  constexpr T&       operator[](usize index) { return elements[index]; }
  constexpr T const& operator[](usize index) const { return elements[index]; }

  constexpr vector& operator=(vector const& other);
  constexpr vector& operator=(vector&& other);

  std::array<T, Dimension> elements;
};
} // namespace pyrite::math

#endif // PYRITE_MATH_VECTOR_VECTOR_HPP
