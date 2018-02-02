#ifndef PYRITE_MATH_VECTOR_UTILITY_HPP
#define PYRITE_MATH_VECTOR_UTILITY_HPP

#include <utility>

#include <pyrite/math/utility.hpp>
#include <pyrite/math/vector/operators.hpp>
#include <pyrite/math/vector/utility_fwd.hpp>
#include <pyrite/math/vector/vector.hpp>

namespace pyrite::math
{
namespace detail::vector
{
template <typename T, usize Dimension, std::size_t... Index>
constexpr T dot(::pyrite::math::vector<T, Dimension> const& v1,
                ::pyrite::math::vector<T, Dimension> const& v2,
                std::index_sequence<Index...>)
{
  return (... + (v1[Index] * v2[Index]));
}
} // namespace detail::vector

template <typename T, usize Dimension>
constexpr T dot(vector<T, Dimension> const& v1, vector<T, Dimension> const& v2)
{
  return detail::vector::dot(v1, v2, std::make_index_sequence<Dimension>{});
}

template <typename T, usize Dimension>
constexpr T
  distance(vector<T, Dimension> const& lhs, vector<T, Dimension> const& rhs)
{
  return sqrt(distance_squared(lhs, rhs));
}

template <typename T, usize Dimension>
constexpr T distance_squared(vector<T, Dimension> const& lhs,
                             vector<T, Dimension> const& rhs)
{
  T result{0};
  for (usize i = 0; i < Dimension; ++i)
  {
    result += power(lhs[i] - rhs[i], 2);
  }
  return result;
}

template <typename T, usize Dimension>
constexpr T length_squared(vector<T, Dimension> const& v)
{
  return distance_squared(v, vector<T, Dimension>{});
}

template <typename T, usize Dimension>
constexpr T length(vector<T, Dimension> const& v)
{
  return distance(v, vector<T, Dimension>{});
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>& normalize(vector<T, Dimension>& v)
{
  auto const len = length(v);
  return equal(len, T{0}) ? v : v / len;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension> normalize(vector<T, Dimension> const& v)
{
  return normalize(vector<T, Dimension>(v));
}
} // namespace pyrite::math

#endif // PYRITE_MATH_VECTOR_UTILITY_HPP
