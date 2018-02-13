#ifndef GRAPHICS_COLOR_TEST_HPP
#define GRAPHICS_COLOR_TEST_HPP

#include <pyrite/graphics/color.hpp>

#include "gtest/gtest.h"

#include "utility.h"

#include <limits>
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

  static void equal(color_type const& a, color_type const& b)
  {
    equal(a, b.r, b.g, b.b, b.a);
  }

  static void equal(color_type const& c,
                    value_type        r,
                    value_type        g,
                    value_type        b,
                    value_type        a)
  {
    {
      SCOPED_TRACE("r");
      expect_equal(c.r, r);
    }
    {
      SCOPED_TRACE("g");
      expect_equal(c.g, g);
    }
    {
      SCOPED_TRACE("b");
      expect_equal(c.b, b);
    }
    {
      SCOPED_TRACE("a");
      expect_equal(c.a, a);
    }
  }

  static auto to_string(color_type const& color)
  {
    return "(r: " + std::to_string(color.r) +
           ", g: " + std::to_string(color.g) +
           ", b: " + std::to_string(color.b) +
           ", a: " + std::to_string(color.a) + ")";
  }
};

TYPED_TEST_CASE_P(graphics_color_test);
} // namespace test

#endif // GRAPHICS_COLOR_TEST_HPP
