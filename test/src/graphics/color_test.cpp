#include "graphics/color_test.h"

#include <pyrite/core/type.hpp>

inline namespace test
{
namespace
{
using namespace ::pyrite;
using ::pyrite::graphics::color;

TYPED_TEST_P(graphics_color_test, constructor)
{
  using value_type         = typename TestFixture::value_type;
  using color_type         = typename TestFixture::color_type;
  constexpr auto max_value = TestFixture::max_value;
  constexpr auto zero      = TestFixture::zero;

  constexpr auto r = max_value / 4 * 1;
  constexpr auto g = max_value / 4 * 2;
  constexpr auto b = max_value / 4 * 3;
  constexpr auto a = max_value / 4 * 4;

  constexpr color_type c;
  TestFixture::expect_equal(c, zero, zero, zero, max_value, "default");

  constexpr color_type c2{r, g, b};
  TestFixture::expect_equal(c2, r, g, b, max_value, "color(r, g, b)");

  constexpr color_type c3{r, g, b, a};
  TestFixture::expect_equal(c3, r, g, b, a, "color(r, g, b, a)");

  constexpr color_type c4{c3};
  TestFixture::expect_equal(c4, c3);

  auto const make_color_element = [](u8 v) {
    auto const elm_ld = (static_cast<long double>(v) / 0xff) * max_value;
    return static_cast<value_type>(elm_ld);
  };
  constexpr color_type c5{0xffaa9908};
  TestFixture::expect_equal(c5,
                            make_color_element(0xff),
                            make_color_element(0xaa),
                            make_color_element(0x99),
                            make_color_element(0x08),
                            "color(color<U>)");
}

template <typename From, typename To>
void convert_test(color<From> const& c)
{
  SCOPED_TRACE("convert constructor : from " +
               graphics_color_test<From>::to_string(c));
  auto const converted = c.template convert<To>();

  graphics_color_test<To>::expect_equal(converted, color<To>{c});
  graphics_color_test<To>::expect_equal(converted,
                                        convert_value<From, To>(c.r),
                                        convert_value<From, To>(c.g),
                                        convert_value<From, To>(c.b),
                                        convert_value<From, To>(c.a));
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
  constexpr value_type a = max_value / 3;

  [[maybe_unused]] constexpr color_type c{r, g, b, a};
#define cvt_test(type)                                                         \
  {                                                                            \
    SCOPED_TRACE("to " #type);                                                 \
    convert_test<value_type, type>(c);                                         \
  }

  cvt_test(u8);
  cvt_test(i16);
  cvt_test(u16);
  cvt_test(i32);
  cvt_test(f32);
  cvt_test(f64);
#undef cvt_test
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

TYPED_TEST_P(graphics_color_test, assignment_operators)
{
  using value_type = typename TestFixture::value_type;
  using color_type = color<value_type>;

  for (int i = 0; i < 256; ++i)
  {
    color_type c1{TestFixture::get_random_color()};
    color_type c2, c3;
    c2 = c1;
    TestFixture::expect_equal(c1, c2);

    c3 = std::move(c1);
    TestFixture::expect_equal(c2, c3);
  }
}

TYPED_TEST_P(graphics_color_test, operators)
{
  using value_type = typename TestFixture::value_type;
  //using color_type = color<value_type>;

#define test_operator_x_eq(op)                                                 \
  {                                                                            \
    auto const c1   = TestFixture::get_random_color();                         \
    auto const c2   = TestFixture::get_random_color();                         \
    auto       c3   = c1;                                                      \
    c3         op## = c2;                                                      \
                                                                               \
    if constexpr (std::is_floating_point_v<value_type>)                        \
    {                                                                          \
      TestFixture::expect_equal(                                               \
        c3, c1.r op c2.r, c1.g op c2.g, c1.b op c2.b, c1.a op c2.a);           \
    }                                                                          \
    else                                                                       \
    {                                                                          \
      auto c4   = c1.template convert<long double>();                          \
      c4   op## = c2.template convert<long double>();                          \
      TestFixture::expect_equal(c3, c4.template convert<value_type>());        \
    }                                                                          \
  }

#define test_binary_operator(op)                                               \
  {                                                                            \
    auto const c1 = TestFixture::get_random_color();                           \
    auto const c2 = TestFixture::get_random_color();                           \
    auto const c3 = c1 op c2;                                                  \
                                                                               \
    if constexpr (std::is_floating_point_v<value_type>)                        \
    {                                                                          \
      TestFixture::expect_equal(                                               \
        c3, c1.r op c2.r, c1.g op c2.g, c1.b op c2.b, c1.a op c2.a);           \
    }                                                                          \
    else                                                                       \
    {                                                                          \
      using ld      = long double;                                             \
      auto const c4 = c1.template convert<ld>() op c2.template convert<ld>();  \
      TestFixture::expect_equal(c3, c4.template convert<value_type>());        \
    }                                                                          \
  }

  for (int i = 0; i < 256; ++i)
  {
    test_operator_x_eq(+);
    test_operator_x_eq(-);
    test_operator_x_eq(*);
    test_operator_x_eq(/);

    test_binary_operator(+);
    test_binary_operator(-);
    test_binary_operator(*);
    test_binary_operator(/);
  }

#undef test_operator_x_eq
}

REGISTER_TYPED_TEST_CASE_P(graphics_color_test,
                           constructor,
                           convert,
                           vector_convert,
                           assignment_operators,
                           operators);
using test_case = ::testing::Types<u8, u16, i16, i32, f32, f64>;
INSTANTIATE_TYPED_TEST_CASE_P(default_test, graphics_color_test, test_case);
} // namespace
} // namespace test