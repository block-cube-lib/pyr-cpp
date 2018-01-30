#include <pyrite/math/angle.hpp>

#include "gtest/gtest.h"
namespace
{
using namespace pyrite::math;

template <typename T, typename F>
constexpr auto loop(T begin, T end, F func)
{
  for (T i = begin; i <= end; ++i)
  {
    func(i);
  }
}

TEST(angle_test, constructor)
{
  // default
  angle<double> a;
  EXPECT_EQ(a.degree(), 0.0);

  // degree
  loop(0, 360, [](int i) {
    angle<float> a(i, degree_tag);
    EXPECT_FLOAT_EQ(a.degree(), static_cast<float>(i));
  });

  // radian
  loop(0, 360, [](int i) {
    const auto   rad = pi<float> / 180 * i;
    angle<float> a(rad, radian_tag);
    EXPECT_FLOAT_EQ(a.radian(), rad);
  });

  // copy
  loop(0, 360, [](int i) {
    const auto   rad = pi<float> / 180 * i;
    angle<float> a(rad, radian_tag);
    angle<float> b(a);
    EXPECT_FLOAT_EQ(b.radian(), rad);
  });

  // move
  loop(0, 360, [](int i) {
    const auto   rad = pi<float> / 180 * i;
    angle<float> a(rad, radian_tag);
    angle<float> b(std::move(a));
    EXPECT_FLOAT_EQ(b.radian(), rad);
  });
}

TEST(angle_test, rotate)
{
  loop(-4200, 4200, [](int i) {
    float const  init_degree = i / 10;
    angle<float> a(init_degree, degree_tag);
    float const  add_degree = i + 42;
    a.rotate({add_degree, degree_tag});
    EXPECT_FLOAT_EQ(a.degree(), (init_degree + add_degree));
  });
}

TEST(angle_test, radian)
{
  loop(-360, 360, [](int i) {
    float const  rad = i * pi<float> / 180;
    angle<float> a{rad, radian_tag};
    EXPECT_FLOAT_EQ(a.radian(), rad);
  });
}

TEST(angle_test, degree)
{
  loop(-360, 360, [](int i) {
    float const  deg = i;
    angle<float> a{deg, degree_tag};
    EXPECT_FLOAT_EQ(a.degree(), deg);
  });
}

TEST(angle_test, sin)
{
  loop(-360, 360, [](int i) {
    float const  rad = i * pi<float> / 180;
    angle<float> a{rad, radian_tag};
    EXPECT_FLOAT_EQ(a.sin(), sin(rad));
  });
}

TEST(angle_test, cos)
{
  loop(-360, 360, [](int i) {
    float const  rad = i * pi<float> / 180;
    angle<float> a{rad, radian_tag};
    EXPECT_FLOAT_EQ(a.cos(), cos(rad));
  });
}

TEST(angle_test, tan)
{
  loop(-360, 360, [](int i) {
    float const  rad = i * pi<float> / 180;
    angle<float> a{rad, radian_tag};
    EXPECT_FLOAT_EQ(a.tan(), tan(rad));
  });
}

TEST(angle_test, equality_operator)
{
  loop(-360, 360, [](int i) {
    angle<float> a(i, degree_tag);
    angle<float> b(a);
    angle<float> c(i + 1, degree_tag);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);

    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
  });
}

TEST(angle_test, copy_and_move_assignment)
{
  loop(-360, 360, [](int i) {
    float const  rad = degree_to_radian(i);
    angle<float> a(rad, radian_tag);
    angle<float> b;
    angle<float> c;

    b = a;
    c = std::move(a);

    EXPECT_FLOAT_EQ(b.radian(), rad);
    EXPECT_FLOAT_EQ(c.radian(), rad);
  });
}

TEST(angle_test, operators)
{
  loop(-360, 360, [](int i) {
    float const  rad1 = i * pi<float> / 180;
    float const  rad2 = (i + 42) * pi<float> / 180;
    angle<float> a{rad1, radian_tag};
    angle<float> b{rad2, radian_tag};
    float const  v{23.0f};

    EXPECT_FLOAT_EQ((a + b).radian(), (rad1 + rad2));
    EXPECT_FLOAT_EQ((a - b).radian(), (rad1 - rad2));
    EXPECT_FLOAT_EQ((a * v).radian(), (rad1 * v));
    EXPECT_FLOAT_EQ((a / v).radian(), (rad1 / v));

    {
      angle<float> c{a};
      EXPECT_FLOAT_EQ((c += b).radian(), (rad1 + rad2));
      c = a;
      EXPECT_FLOAT_EQ((c -= b).radian(), (rad1 - rad2));
      c = a;
      EXPECT_FLOAT_EQ((c *= v).radian(), (rad1 * v));
      c = a;
      EXPECT_FLOAT_EQ((c /= v).radian(), (rad1 / v));
    }

    angle<float> c{a};
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(a < c);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);

    EXPECT_TRUE(b > a);
    EXPECT_FALSE(c > a);
    EXPECT_TRUE(b >= a);
    EXPECT_TRUE(c >= a);
  });
}
} // namespace
