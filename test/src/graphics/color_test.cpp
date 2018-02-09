#include <pyrite/graphics/color.hpp>

#include "gtest/gtest.h"

#include "utility.h"

#include <limits>
#include <type_traits>

#include <pyrite/core/type.hpp>

inline namespace test
{
using namespace ::pyrite;
using namespace ::pyrite::graphics;

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
  using color_type             = color<T>;
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
    return "(r: " + std::to_string(color.r) + "g: " + std::to_string(color.g) +
           "b: " + std::to_string(color.b) + "a: " + std::to_string(color.a) +
           ")";
  }
};

TYPED_TEST_CASE_P(graphics_color_test);

TYPED_TEST_P(graphics_color_test, constructor)
{
  //using value_type         = typename TestFixture::value_type;
  using color_type         = typename TestFixture::color_type;
  constexpr auto max_value = TestFixture::max_value;
  constexpr auto zero      = TestFixture::zero;

  constexpr auto r = max_value / 4 * 1;
  constexpr auto g = max_value / 4 * 2;
  constexpr auto b = max_value / 4 * 3;
  constexpr auto a = max_value / 4 * 4;

  constexpr color_type c;
  TestFixture::equal(c, zero, zero, zero, max_value);

  constexpr color_type c2{r, g, b};
  TestFixture::equal(c2, r, g, b, max_value);

  constexpr color_type c3{r, g, b, a};
  TestFixture::equal(c3, r, g, b, a);

  constexpr color_type c4{c3};
  TestFixture::equal(c4, c3);
}

template <typename From, typename To = long double>
void convert_test(color<From> const& c)
{
  [[maybe_unused]] auto const converted = c.template convert<To>();
  {
    SCOPED_TRACE("convert constructor : from " +
                 graphics_color_test<From>::to_string(c));
    graphics_color_test<To>::equal(converted, color<To>{c});
    graphics_color_test<From>::equal(c, converted.template convert<From>());
  }
}

TYPED_TEST_P(graphics_color_test, convert)
{
  using value_type               = typename TestFixture::value_type;
  using color_type               = color<value_type>;
  constexpr value_type max_value = TestFixture::max_value;
  constexpr value_type min_value = TestFixture::min_value;
  constexpr value_type zero      = TestFixture::zero;

  constexpr value_type r = min_value;
  constexpr value_type g = max_value;
  constexpr value_type b = zero;
  constexpr value_type a = max_value / 2;

  [[maybe_unused]] constexpr color_type c{r, g, b, a};
  convert_test(c);
}

TYPED_TEST_P(graphics_color_test, vector_convert)
{
  using value_type        = typename TestFixture::value_type;
  using color_type        = color<value_type>;
  using vector_value_type = std::
    conditional_t<std::is_floating_point_v<value_type>, value_type, double>;
  using vector_type = pyrite::math::vector<vector_value_type, 4>;

  {
    [[maybe_unused]] constexpr color_type  c{};
    [[maybe_unused]] constexpr auto        v = vector_type(c);
    [[maybe_unused]] constexpr vector_type v2(c);
    [[maybe_unused]] constexpr vector_type v3{c};
  }

  {
    [[maybe_unused]] constexpr vector_type v{};
    [[maybe_unused]] constexpr auto        c = color_type(v);
    [[maybe_unused]] constexpr color_type  c2(v);
    [[maybe_unused]] constexpr color_type  c3{v};
  }
}

REGISTER_TYPED_TEST_CASE_P(graphics_color_test,
                           constructor,
                           convert,
                           vector_convert);
using test_case = ::testing::Types<u8, u16, i16, i32, f32, f64>;
INSTANTIATE_TYPED_TEST_CASE_P(default_test, graphics_color_test, test_case);
} // namespace test
