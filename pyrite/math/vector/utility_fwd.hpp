#ifndef PYRITE_MATH_VECTOR_UTILITY_FWD_HPP
#define PYRITE_MATH_VECTOR_UTILITY_FWD_HPP

#include <pyrite/math/vector/vector_fwd.hpp>

namespace pyrite::math
{
template <typename T, usize Dimension>
constexpr T dot(vector<T, Dimension> const& v1, vector<T, Dimension> const& v2);

template <typename T, usize Dimension>
constexpr T
  distance(vector<T, Dimension> const& lhs, vector<T, Dimension> const& rhs);

template <typename T, usize Dimension>
constexpr T distance_squared(vector<T, Dimension> const& lhs,
                             vector<T, Dimension> const& rhs);

template <typename T, usize Dimension>
constexpr T length_squared(vector<T, Dimension> const& v);

template <typename T, usize Dimension>
constexpr T length(vector<T, Dimension> const& v);

template <typename T, usize Dimension>
constexpr vector<T, Dimension>& normalize(vector<T, Dimension>& v);

template <typename T, usize Dimension>
constexpr vector<T, Dimension> normalize(vector<T, Dimension> const& v);

template <typename T, usize Dimension>
constexpr vector<T, Dimension>& normalize(vector<T, Dimension>& v);

template <typename T, usize Dimension>
constexpr vector<T, Dimension> normalized(vector<T, Dimension> const& v);
} // namespace pyrite::math

#endif // PYRITE_MATH_VECTOR_UTILITY_FWD_HPP
