#ifndef PYRITE_VECTOR_VECTOR_OPERATORS_HPP
#define PYRITE_VECTOR_VECTOR_OPERATORS_HPP

#include <pyrite/core/type.hpp>
#include <pyrite/math/utility.hpp>
#include <pyrite/math/vector.hpp>

namespace pyrite::math
{
namespace detail::vector
{
using ::pyrite::math::vector;

template <typename T, usize Dimension, typename Operator>
constexpr vector<T, Dimension>&
  loop(vector<T, Dimension>& lhs, vector<T, Dimension> const& rhs, Operator op)
{
  for (usize i = 0; i < Dimension; ++i)
  {
    op(lhs[i], rhs[i]);
  }

  return lhs;
}
} // namespace detail::vector

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

} // namespace pyrite::math

#endif // PYRITE_VECTOR_VECTOR_OPERATORS_HPP
