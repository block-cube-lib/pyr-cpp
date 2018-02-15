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

template <typename T>
constexpr color<T>::color(u32 rrggbbaa) noexcept
  : color(color<u8>(static_cast<u8>((rrggbbaa >> 24) & 0x0ff),
                    static_cast<u8>((rrggbbaa >> 16) & 0x0ff),
                    static_cast<u8>((rrggbbaa >> 8) & 0x0ff),
                    static_cast<u8>(rrggbbaa & 0x0ff)))
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

template <typename T>
constexpr T& color<T>::operator[](usize index)
{
  assert(0 <= index && index < 4); // out of range
  if (index == 0)
  {
    return r;
  }
  else if (index == 1)
  {
    return g;
  }
  else if (index == 2)
  {
    return b;
  }
  else
  {
    return a;
  }
}

template <typename T>
constexpr T const& color<T>::operator[](usize index) const
{
  assert(0 <= index && index < 4); // out of range
  if (index == 0)
  {
    return r;
  }
  else if (index == 1)
  {
    return g;
  }
  else if (index == 2)
  {
    return b;
  }
  else
  {
    return a;
  }
}

template <typename T>
constexpr bool operator==(color<T> const& lhs, color<T> const& rhs) noexcept
{
  return pyrite::math::equal(lhs.r, rhs.r) &&
         pyrite::math::equal(lhs.g, rhs.g) &&
         pyrite::math::equal(lhs.b, rhs.b) && pyrite::math::equal(lhs.a, rhs.a);
}

template <typename T>
constexpr bool operator!=(color<T> const& lhs, color<T> const& rhs) noexcept
{
  return !(lhs == rhs);
}

template <typename T>
constexpr color<T>& operator+=(color<T>& lhs, color<T> const& rhs) noexcept
{
  if constexpr (std::is_floating_point_v<T>)
  {
    lhs.r += rhs.r;
    lhs.g += rhs.g;
    lhs.a += rhs.a;
    lhs.b += rhs.b;
  }
  else
  {
    auto lhs_ld = lhs.template convert<long double>();
    lhs_ld += rhs.template convert<long double>();
    lhs = lhs_ld.template convert<T>();
  }
  return lhs;
}

template <typename T>
constexpr color<T>& operator-=(color<T>& lhs, color<T> const& rhs) noexcept
{
  if constexpr (std::is_floating_point_v<T>)
  {
    lhs.r -= rhs.r;
    lhs.g -= rhs.g;
    lhs.a -= rhs.a;
    lhs.b -= rhs.b;
  }
  else
  {
    auto lhs_ld = lhs.template convert<long double>();
    lhs_ld -= rhs.template convert<long double>();
    lhs = lhs_ld.template convert<T>();
  }
  return lhs;
}

template <typename T>
constexpr color<T>& operator*=(color<T>& lhs, color<T> const& rhs) noexcept
{
  if constexpr (std::is_floating_point_v<T>)
  {
    lhs.r *= rhs.r;
    lhs.g *= rhs.g;
    lhs.a *= rhs.a;
    lhs.b *= rhs.b;
  }
  else
  {
    auto lhs_ld = lhs.template convert<long double>();
    lhs_ld *= rhs.template convert<long double>();
    lhs = lhs_ld.template convert<T>();
  }
  return lhs;
}

template <typename T>
constexpr color<T>& operator/=(color<T>& lhs, color<T> const& rhs)
{
  if constexpr (std::is_floating_point_v<T>)
  {
    lhs.r /= rhs.r;
    lhs.g /= rhs.g;
    lhs.a /= rhs.a;
    lhs.b /= rhs.b;
  }
  else
  {
    auto lhs_ld = lhs.template convert<long double>();
    lhs_ld /= rhs.template convert<long double>();
    lhs = lhs_ld.template convert<T>();
  }
  return lhs;
}

template <typename T>
constexpr color<T>& operator*=(color<T>& c, T v) noexcept
{
  if constexpr (std::is_floating_point_v<T>)
  {
    c.r *= v;
    c.g *= v;
    c.a *= v;
    c.b *= v;
  }
  else
  {
    auto c_ld = c.template convert<long double>();
    c_ld *= static_cast<long double>(v);
    c = c_ld.template convert<T>();
  }
  return c;
}

template <typename T>
constexpr color<T>& operator/=(color<T>& c, T v)
{
  if constexpr (std::is_floating_point_v<T>)
  {
    c.r /= v;
    c.g /= v;
    c.a /= v;
    c.b /= v;
  }
  else
  {
    auto c_ld = c.template convert<long double>();
    c_ld /= static_cast<long double>(v);
    c = c_ld.template convert<T>();
  }
  return c;
}

template <typename T>
constexpr color<T> operator+(color<T> lhs, color<T> const& rhs) noexcept
{
  return lhs += rhs;
}

template <typename T>
constexpr color<T> operator-(color<T> lhs, color<T> const& rhs) noexcept
{
  return lhs -= rhs;
}

template <typename T>
constexpr color<T> operator*(color<T> lhs, color<T> const& rhs) noexcept
{
  return lhs *= rhs;
}

template <typename T>
constexpr color<T> operator/(color<T> lhs, color<T> const& rhs)
{
  return lhs /= rhs;
}

template <typename T>
constexpr color<T> operator*(color<T> c, T v) noexcept
{
  return c *= v;
}

template <typename T>
constexpr color<T> operator/(color<T> c, T v)
{
  return c /= v;
}

/******************************************************************************
 * detail
 ******************************************************************************/
namespace detail::color
{
template <typename T>
constexpr bool is_real = std::is_floating_point_v<T>;
template <typename T>
constexpr bool is_integeral = std::is_integral_v<T>;
template <typename T>
constexpr bool is_int = std::is_signed_v<T>&& std::is_integral_v<T>;
template <typename T>
constexpr bool is_uint = std::is_unsigned_v<T>&& std::is_integral_v<T>;

template <typename To, typename From>
constexpr To convert(From from)
{
  constexpr auto from_max = std::numeric_limits<From>::max();
  constexpr auto from_min = std::numeric_limits<From>::min();
  constexpr auto to_max   = std::numeric_limits<To>::max();
  constexpr auto to_min   = std::numeric_limits<To>::min();

  auto const to_real = [](auto v) { return static_cast<long double>(v); };

  if constexpr (std::is_same_v<From, To>) // same
  {
    return from;
  }
  else if constexpr (is_real<From> && is_real<To>) // real to real
  {
    return static_cast<To>(from);
  }
  else if constexpr (is_uint<From> && is_real<To>) // uint to real
  {
    return static_cast<To>(to_real(from) / from_max);
  }
  else if constexpr (is_int<From> && is_real<To>) // int to real
  {
    if (0 <= from)
    {
      return static_cast<To>(to_real(from) / from_max);
    }
    else // if(from < 0)
    {
      return -static_cast<To>(to_real(from) / from_min);
    }
  }
  else if constexpr (is_int<From> && is_int<To>) // int to int
  {
    if (0 <= from)
    {
      auto const v = to_real(from) / from_max * to_max;
      return static_cast<To>(v);
    }
    else
    {
      auto const v = to_real(from) / from_min * to_min;
      return static_cast<To>(v);
    }
  }
  else if constexpr (is_int<From> && is_uint<To>) // int to uint
  {
    if (from < 0)
    {
      return From{0};
    }
    auto const v = from / to_real(from_max);
    return static_cast<To>(v * to_max);
  }
  else if constexpr ((is_uint<From> && is_int<To>) || // uint to int
                     (is_uint<From> && is_uint<To>))  // uint to uint
  {
    auto const v = to_real(from) / from_max * to_max;
    return static_cast<To>(v);
  }
  else if constexpr (is_real<From> && is_int<To>) // real to int
  {
    auto const v = pyrite::clamp(to_real(from), -1.0l, 1.0l);
    if (0.0l <= v)
    {
      return static_cast<To>(v * to_max);
    }
    else
    {
      return static_cast<To>(-v * to_min);
    }
  }
  else if constexpr (is_real<From> && is_uint<To>) // real to uint
  {
    auto const v = pyrite::clamp(to_real(from), 0.0l, 1.0l);
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
