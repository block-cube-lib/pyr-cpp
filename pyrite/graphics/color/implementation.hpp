#ifndef PYRITE_GRAPHICS_COLOR_IMPLEMENTATION_HPP
#define PYRITE_GRAPHICS_COLOR_IMPLEMENTATION_HPP

#include <limits>
#include <utility>

#include <pyrite/mpl/false_v.hpp>
#include <pyrite/utility.hpp>

namespace pyrite::graphics
{
namespace detail::color
{
template <typename To, typename From>
constexpr To convert(From from);
}

/******************************************************************************
 * constructor
 ******************************************************************************/
template <typename T>
constexpr color<T>::color(T r, T g, T b, T a) noexcept : r{r}, g{g}, b{b}, a{a}
{
}

template <typename T> // from
template <typename U> // to
constexpr color<T>::color(color<U> const& other)
  : r{detail::color::convert<T>(other.r)}
  , g{detail::color::convert<T>(other.g)}
  , b{detail::color::convert<T>(other.b)}
  , a{detail::color::convert<T>(other.a)}
{
}

template <typename T>
template <typename U>
constexpr color<T>::color(pyrite::math::vector<U, 4> const& v)
  : color(color<U>(v.x, v.y, v.z, v.w).template convert<T>())
{
}

/******************************************************************************
 * member function
 ******************************************************************************/
template <typename T> // from
template <typename U> // to
constexpr color<U> color<T>::convert() const
{
  return {detail::color::convert<U>(r),
          detail::color::convert<U>(g),
          detail::color::convert<U>(b),
          detail::color::convert<U>(a)};
}

/******************************************************************************
 * operator
 ******************************************************************************/
template <typename T>
color<T>& color<T>::operator=(color<T> const& other) noexcept
{
  if (this != &other)
  {
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
  }
  return *this;
}

template <typename T>
color<T>& color<T>::operator=(color<T>&& other) noexcept
{
  if (this != &other)
  {
    r = std::move(other.r);
    g = std::move(other.g);
    b = std::move(other.b);
    a = std::move(other.a);
  }
  return *this;
}

template <typename T>
template <typename U>
constexpr color<T>::operator pyrite::math::vector<U, 4>() const
{
  auto const c = convert<U>();
  return {c.r, c.g, c.b, c.a};
}

/******************************************************************************
 * detail
 ******************************************************************************/
namespace detail::color
{
template <typename T>
constexpr bool is_floating_point = std::is_floating_point_v<T>;
template <typename T>
constexpr bool is_integeral = std::is_integral_v<T>;
template <typename T>
constexpr bool          is_signed_integeral =
  std::is_signed_v<T>&& std::is_integral_v<T>;
template <typename T>
constexpr bool            is_unsigned_integeral =
  std::is_unsigned_v<T>&& std::is_integral_v<T>;

template <typename To, typename From>
constexpr To convert(From from)
{
  constexpr auto from_max = std::numeric_limits<From>::max();
  constexpr auto from_min = std::numeric_limits<From>::min();
  constexpr auto to_max   = std::numeric_limits<To>::max();
  constexpr auto to_min   = std::numeric_limits<To>::min();

  auto const round = [](long double v) {
    if (-0.5l < v && v < 0.5l)
    {
      return 0.0l;
    }
    else if (v < 0)
    {
      return static_cast<long double>(static_cast<i64>(v + 0.5l));
    }
    else // if(0 < v)
    {
      return static_cast<long double>(static_cast<i64>(v - 0.5l));
    }
  };

  if constexpr (std::is_same_v<From, To>)
  {
    return from;
  }
  else if constexpr (is_floating_point<From> && is_floating_point<To>)
  {
    return static_cast<To>(from);
  }
  else if constexpr (is_unsigned_integeral<From> && is_floating_point<To>)
  {
    return static_cast<To>(static_cast<long double>(from) / from_max);
  }
  else if constexpr (is_signed_integeral<From> && is_floating_point<To>)
  {
    if (0 <= from)
    {
      return static_cast<To>(static_cast<long double>(from) / from_max);
    }
    else // if(from < 0)
    {
      return -static_cast<To>(static_cast<long double>(from) / from_min);
    }
  }
  else if constexpr (is_signed_integeral<From> && is_signed_integeral<To>)
  {
    if (0 <= from)
    {
      auto const v = round(static_cast<long double>(from) / from_max * to_max);
      return static_cast<To>(v);
    }
    else
    {
      auto const v = round(static_cast<long double>(from) / from_min * to_min);
      return static_cast<To>(v);
    }
  }
  else if constexpr (is_signed_integeral<From> && is_unsigned_integeral<To>)
  {
    if (from < 0)
    {
      from = 0;
    }
    auto const v = from / static_cast<long double>(from_max);
    return static_cast<To>(round(v * to_max));
  }
  else if constexpr ((is_unsigned_integeral<From> && is_signed_integeral<To>) ||
                     (is_unsigned_integeral<From> && is_unsigned_integeral<To>))
  {
    auto const v = static_cast<long double>(from) / from_max * to_max;
    return static_cast<To>(round(v));
  }
  else if constexpr (is_floating_point<From> && is_signed_integeral<To>)
  {
    auto const v = pyrite::clamp(static_cast<long double>(from), -1.0l, 1.0l);
    if (0.0l <= v)
    {
      return static_cast<To>(v * to_max);
    }
    else
    {
      return static_cast<To>(-v * to_min);
    }
  }
  else if constexpr (is_floating_point<From> && is_unsigned_integeral<To>)
  {
    auto const v = pyrite::clamp(static_cast<long double>(from), 0.0l, 1.0l);
    return static_cast<To>(v * to_max);
  }
  else
  {
    static_assert(mpl::false_v<To>);
  }
}
} // namespace detail::color
} // namespace pyrite::graphics

#endif // PYRITE_GRAPHICS_COLOR_IMPLEMENTATION_HPP
