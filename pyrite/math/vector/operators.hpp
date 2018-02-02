#ifndef PYRITE_VECTOR_VECTOR_OPERATORS_HPP
#define PYRITE_VECTOR_VECTOR_OPERATORS_HPP

#include <pyrite/core/type.hpp>
#include <pyrite/math/utility.hpp>
#include <pyrite/math/vector.hpp>

namespace pyrite::math
{
template <typename T, usize Dimension>
constexpr bool
  operator==(vector<T, Dimension> const& lhs, vector<T, Dimension> const& rhs)
{
  bool result = true;
  for (usize i = 0; result && i < Dimension; ++i)
  {
    result = result && equal(lhs[i], rhs[i]);
  }
  return result;
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
