#ifndef PYRITE_UTILITY_CLAMP_HPP
#define PYRITE_UTILITY_CLAMP_HPP

#include <utility>

namespace pyrite
{
inline namespace utility
{
/**
 * if b compares less than min, return min;
 * otherwise if max compares less than v, return max;
 * otherwise returns v.
 *
 * @tparam T clamp value type.
 * @param v   the value to clamp.
 * @param min the boundaries to clamp to v.
 * @param max the boundaries to clamp to v.
 *
 * @return reference to min if v is less than min,
 *         reference to max if max is less than v, otherwise reference to v.
 */
template <typename T>
constexpr T const& clamp(T const& v, T const& min, T const& max)
{
  return v < min ? min : (max < v ? max : v);
}

/**
 * if b compares less than min, return min;
 * otherwise if max compares less than v, return max;
 * otherwise returns v.
 *
 * @tparam T clamp value type.
 * @param v    the value to clamp.
 * @param min  the boundaries to clamp to v.
 * @param max  the boundaries to clamp to v.
 * @param comp comparison function object.
 *
 * @return reference to min if v is less than min,
 *         reference to max if max is less than v, otherwise reference to v.
 */
template <typename T, typename Compare>
constexpr T const& clamp(T const& v, T const& min, T const& max, Compare comp)
{
  return comp(v, min) ? min : (comp(max, v) ? max : v);
}
} // namespace utility
} // namespace pyrite

#endif // PYRITE_UTILITY_CLAMP_HPP
