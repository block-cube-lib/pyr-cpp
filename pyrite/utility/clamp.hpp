#ifndef PYRITE_UTILITY_CLAMP_HPP
#define PYRITE_UTILITY_CLAMP_HPP

#include <utility>

namespace pyrite
{
inline namespace utility
{
template <typename T>
constexpr T const& clamp(T const& v, T const& min, T const& max)
{
  return v < min ? min : (max < v ? max : v);
}

template <typename T, typename Compare>
constexpr T const& clamp(T const& v, T const& min, T const& max, Compare comp)
{
  return comp(v, min) ? min : (comp(max, v) ? max : v);
}
} // namespace utility
} // namespace pyrite

#endif // PYRITE_UTILITY_CLAMP_HPP
