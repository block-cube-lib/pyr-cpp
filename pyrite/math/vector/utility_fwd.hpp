#ifndef PYRITE_MATH_VECTOR_UTILITY_FWD_HPP
#define PYRITE_MATH_VECTOR_UTILITY_FWD_HPP

#include <pyrite/math/vector/vector_fwd.hpp>

namespace pyrite::math
{
/**
 * returns the dot product of two vectors.
 *
 * @param v1 the first vector.
 * @param v2 the second vector.
 * @return the dot product.
 */
template <typename T, usize Dimension>
constexpr T dot(vector<T, Dimension> const& v1, vector<T, Dimension> const& v2);

/**
 * returns the Euclidean distance between the two given points.
 *
 * @param v1 the first vector.
 * @param v2 the second vector.
 * @return the distance.
 */
template <typename T, usize Dimension>
constexpr T
  distance(vector<T, Dimension> const& v1, vector<T, Dimension> const& v2);

/**
 * returns the Euclidean distance squared between the two given points.
 *
 * @param v1 the first vector.
 * @param v2 the second vector.
 * @return the distance squared.
 */
template <typename T, usize Dimension>
constexpr T distance_squared(vector<T, Dimension> const& lhs,
                             vector<T, Dimension> const& rhs);

/**
 * returns the length of the vector.
 *
 * @param v vector.
 * @param the vector's length.
 */
template <typename T, usize Dimension>
constexpr T length(vector<T, Dimension> const& v);

/**
 * returns the length of the vector squared.
 *
 * @param v vector.
 * @param the vector's length squared.
 */
template <typename T, usize Dimension>
constexpr T length_squared(vector<T, Dimension> const& v);

/**
 * normalize the specified vector.
 *
 * @param v vector.
 * @return the reference to normalized vector.
 */
template <typename T, usize Dimension>
constexpr vector<T, Dimension>& normalize(vector<T, Dimension>& v);

/**
 * returns a vector with the same direction as the specified vector,
 * but with a length of one.
 *
 * @param v vector.
 * @return the normalized vector.
 */
template <typename T, usize Dimension>
constexpr vector<T, Dimension> normalized(vector<T, Dimension> const& v);
} // namespace pyrite::math

#endif // PYRITE_MATH_VECTOR_UTILITY_FWD_HPP
