#ifndef PYRITE_VECTOR_VECTOR_OPERATORS_HPP
#define PYRITE_VECTOR_VECTOR_OPERATORS_HPP

#include <pyrite/core/type.hpp>
#include <pyrite/math/utility.hpp>
#include <pyrite/math/vector/vector.hpp>

namespace pyrite::math
{
namespace detail::vector
{
template <typename T, usize Dimension, std::size_t... Index>
constexpr auto equal(::pyrite::math::vector<T, Dimension> const& v1,
                     ::pyrite::math::vector<T, Dimension> const& v2,
                     std::index_sequence<Index...>)
{
  return (::pyrite::math::equal(v1[Index], v2[Index]) && ...);
}
} // namespace detail::vector

template <typename T, usize Dimension>
constexpr bool
  operator==(vector<T, Dimension> const& lhs, vector<T, Dimension> const& rhs)
{
  return detail::vector::equal(lhs, rhs, std::make_index_sequence<Dimension>{});
}

template <typename T, usize Dimension>
constexpr bool
  operator!=(vector<T, Dimension> const& lhs, vector<T, Dimension> const& rhs)
{
  return !(lhs == rhs);
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>&
  operator+=(vector<T, Dimension>& lhs, vector<T, Dimension> const& rhs)
{
  for (usize i = 0; i < Dimension; ++i)
  {
    lhs[i] += rhs[i];
  }
  return lhs;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>&
  operator-=(vector<T, Dimension>& lhs, vector<T, Dimension> const& rhs)
{
  for (usize i = 0; i < Dimension; ++i)
  {
    lhs[i] -= rhs[i];
  }
  return lhs;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>&
  operator*=(vector<T, Dimension>& lhs, vector<T, Dimension> const& rhs)
{
  for (usize i = 0; i < Dimension; ++i)
  {
    lhs[i] *= rhs[i];
  }
  return lhs;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>& operator*=(vector<T, Dimension>& vec, T scalar)
{
  for (usize i = 0; i < Dimension; ++i)
  {
    vec[i] *= scalar;
  }
  return vec;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>&
  operator/=(vector<T, Dimension>& lhs, vector<T, Dimension> const& rhs)
{
  for (usize i = 0; i < Dimension; ++i)
  {
    lhs[i] /= rhs[i];
  }
  return lhs;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>& operator/=(vector<T, Dimension>& vec, T scalar)
{
  for (usize i = 0; i < Dimension; ++i)
  {
    vec[i] /= scalar;
  }
  return vec;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>
  operator+(vector<T, Dimension> const& lhs, vector<T, Dimension> const& rhs)
{
  vector<T, Dimension> v{lhs};
  return v += rhs;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>
  operator-(vector<T, Dimension> const& lhs, vector<T, Dimension> const& rhs)
{
  vector<T, Dimension> v{lhs};
  return v -= rhs;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>
  operator*(vector<T, Dimension> const& lhs, vector<T, Dimension> const& rhs)
{
  vector<T, Dimension> v{lhs};
  return v *= rhs;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>
  operator*(vector<T, Dimension> const& vec, T scalar)
{
  vector<T, Dimension> v{vec};
  return v *= scalar;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>
  operator*(T scalar, vector<T, Dimension> const& vec)
{
  return vec * scalar;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>
  operator/(vector<T, Dimension> const& lhs, vector<T, Dimension> const& rhs)
{
  vector<T, Dimension> v{lhs};
  return v /= rhs;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension>
  operator/(vector<T, Dimension> const& vec, T scalar)
{
  vector<T, Dimension> v{vec};
  return v /= scalar;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension> operator+(vector<T, Dimension> const& vec)
{
  return vec;
}

template <typename T, usize Dimension>
constexpr vector<T, Dimension> operator-(vector<T, Dimension> const& vec)
{
  return vec * T{-1};
}

} // namespace pyrite::math

#endif // PYRITE_VECTOR_VECTOR_OPERATORS_HPP
