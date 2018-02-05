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

template <typename T, usize Dimension, std::size_t... Index>
constexpr T distance_squared(::pyrite::math::vector<T, Dimension> const& v1,
                             ::pyrite::math::vector<T, Dimension> const& v2,
                             std::index_sequence<Index...>)
{
  return (... + power(v1[Index] - v2[Index], 2));
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
constexpr T distance_squared(vector<T, Dimension> const& v1,
                             vector<T, Dimension> const& v2)
{
  return detail::vector::distance_squared(
    v1, v2, std::make_index_sequence<Dimension>{});
}

template <typename T, usize Dimension>
constexpr T length_squared(vector<T, Dimension> const& v)
{
  return dot(v, v);
}

template <typename T, usize Dimension>
constexpr T length(vector<T, Dimension> const& v)
{
  return sqrt(length_squared(v));
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>& normalize(vector<T, Dimension>& v)
{
  auto const len_sq = length_squared(v);
  return equal(len_sq, T{0}) ? v : (v /= sqrt(len_sq));
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension> normalized(vector<T, Dimension> const& v)
{
  vector<T, Dimension> vec{v};
  return normalize(vec);
}
} // namespace pyrite::math

#endif // PYRITE_MATH_VECTOR_UTILITY_HPP
