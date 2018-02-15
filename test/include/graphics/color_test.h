#ifndef GRAPHICS_COLOR_TEST_H
#define GRAPHICS_COLOR_TEST_H

#include <pyrite/graphics/color.hpp>

#include "utility.h"
#include "gtest/gtest.h"
#include <limits>
#include <pyrite/random.hpp>
#include <string>
#include <string_view>
#include <type_traits>

inline namespace test
{
template <typename T>
class graphics_color_test : public ::testing::Test
{
private:
  static constexpr std::pair<T, T> make_minmax()
  {
    if constexpr (std::is_floating_point_v<T>)
    {
      return {T{0}, T{1}};
    }
    else
    {
      return {std::numeric_limits<T>::min(), std::numeric_limits<T>::max()};
    }
  }

public:
  using value_type             = T;
  using color_type             = ::pyrite::graphics::color<T>;
  static constexpr T zero      = T{0};
  static constexpr T min_value = make_minmax().first;
  static constexpr T max_value = make_minmax().second;

  static void expect_equal(color_type const& a,
                           color_type const& b,
                           std::string_view  scope = "")
  {
    expect_equal(a, b.r, b.g, b.b, b.a, scope);
  }

  static void expect_equal(color_type const& c,
                           value_type        r,
                           value_type        g,
                           value_type        b,
                           value_type        a,
                           std::string_view  scope = "")
  {
    SCOPED_TRACE(scope);
    SCOPED_TRACE(to_string(c) + " equal " + to_string(color_type(r, g, b, a)));

    ::expect_equal(c.r, r, "r");
    ::expect_equal(c.g, g, "g");
    ::expect_equal(c.b, b, "b");
    ::expect_equal(c.a, a, "a");
  }

  static auto to_string(color_type const& color)
  {
    return "(r: " + std::to_string(color.r) +
           ", g: " + std::to_string(color.g) +
           ", b: " + std::to_string(color.b) +
           ", a: " + std::to_string(color.a) + ")";
  }

  static color_type get_random_color()
  {
    static thread_local pyrite::random random;
    return {random.next<value_type>(),
            random.next<value_type>(),
            random.next<value_type>(),
            random.next<value_type>()};
  }
};

TYPED_TEST_CASE_P(graphics_color_test);

template <typename From, typename To>
To convert_value(From from)
{
  constexpr bool from_is_real = std::is_floating_point_v<From>;
  constexpr bool from_is_int  = std::is_signed_v<From> &&
                               std::is_integral_v<From>;
  constexpr bool from_is_uint = std::is_unsigned_v<From> &&
                                std::is_integral_v<From>;
  constexpr bool to_is_real = std::is_floating_point_v<To>;
  constexpr bool to_is_int  = std::is_signed_v<To> && std::is_integral_v<To>;
  constexpr bool to_is_uint = std::is_unsigned_v<To> && std::is_integral_v<To>;

  constexpr auto from_max = std::numeric_limits<From>::max();
  constexpr auto from_min = std::numeric_limits<From>::min();
  constexpr auto to_max   = std::numeric_limits<To>::max();
  constexpr auto to_min   = std::numeric_limits<To>::min();

  if constexpr (from_is_real && to_is_real)
  {
    return static_cast<To>(from);
  }
  else if constexpr (from_is_real && to_is_int)
  {
    from = pyrite::clamp(from, From{-1}, From{1});
    if (0 <= from)
    {
      return static_cast<To>(static_cast<long double>(from) * to_max);
    }
    else
    {
      return -static_cast<To>(static_cast<long double>(from) * to_min);
    }
  }
  else if constexpr (from_is_real && to_is_uint)
  {
    from = pyrite::clamp(from, From{0}, From{1});
    return static_cast<To>(static_cast<long double>(from) * to_max);
  }
  else if constexpr (from_is_int && to_is_int)
  {
    if (0 <= from)
    {
      auto const v = static_cast<long double>(from) / from_max;
      return convert_value<long double, To>(v);
    }
    else
    {
      auto const v = static_cast<long double>(from) / from_min;
      return convert_value<long double, To>(-v);
    }
  }
  else if constexpr (from_is_int && to_is_uint)
  {
    if (from <= 0)
    {
      return From{0};
    }
    auto const v = static_cast<long double>(from) / from_max;
    return convert_value<long double, To>(v);
  }
  else if constexpr (from_is_int && to_is_real)
  {
    if (0 <= from)
    {
      auto const v = static_cast<long double>(from) / from_max;
      return static_cast<To>(v);
    }
    else
    {
      auto const v = static_cast<long double>(from) / from_min;
      return static_cast<To>(-v);
    }
  }
  else if constexpr (from_is_uint && to_is_real)
  {
    auto const v = static_cast<long double>(from) / from_max;
    return static_cast<To>(v);
  }
  else if constexpr (from_is_uint && to_is_int)
  {
    auto const v = static_cast<long double>(from) / from_max;
    return static_cast<To>(v * to_max);
  }
  else if constexpr (from_is_uint && to_is_uint)
  {
    auto const v = static_cast<long double>(from) / from_max;
    return static_cast<To>(v * to_max);
  }
  else
  {
    return static_cast<To>(from);
  }
}
} // namespace test

#endif // GRAPHICS_COLOR_TEST_H
