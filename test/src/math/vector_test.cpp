#include <pyrite/math/vector.hpp>

#include "gtest/gtest.h"

#include <type_traits>
#include <utility>

namespace
{
/******************************************************************************
 * using
 ******************************************************************************/
using namespace pyrite;
using namespace pyrite::math;

/******************************************************************************
 * test function
 ******************************************************************************/
template <typename T>
void value_equal(T a, T b)
{
  if constexpr (std::is_same_v<T, float>)
  {
    EXPECT_FLOAT_EQ(a, b);
  }
  else if constexpr (std::is_same_v<T, double>)
  {
    EXPECT_DOUBLE_EQ(a, b);
  }
  else
  {
    EXPECT_DOUBLE_EQ(static_cast<double>(a), static_cast<double>(b));
  }
}

template <typename T>
void vector_equal(T const& a, T const& b)
{
  for (usize i = 0; i < T::dimension; ++i)
  {
    value_equal(a[i], b[i]);
  }
}

template <template <typename, pyrite::usize> typename Func,
          typename Seq = std::make_index_sequence<20>>
struct tester;

template <template <typename, pyrite::usize> typename Func, std::size_t... I>
struct tester<Func, std::index_sequence<I...>>
{
  void operator()()
  {
    (void)((Func<float, I + 1>{}(), 0) + ...);
    (void)((Func<double, I + 1>{}(), 0) + ...);
    (void)((Func<long double, I + 1>{}(), 0) + ...);
  }
};

template <typename T,
          usize Dimension,
          typename Sequence = std::make_index_sequence<Dimension>>
struct make_test_array;
template <typename T, usize Dimension, std::size_t... Index>
struct make_test_array<T, Dimension, std::index_sequence<Index...>>
{
  static constexpr T value0[Dimension]{static_cast<T>(Index * 1.1)...};
  static constexpr T value1[Dimension]{static_cast<T>(Index * 2.01)...};
  static constexpr T value2[Dimension]{static_cast<T>(Index * 3.2)...};
};

/******************************************************************************
 * constructors
 ******************************************************************************/
template <typename T, pyrite::usize Dimension>
struct constructor_test
{
  void operator()()
  {
    using vector_type           = vector<T, Dimension>;
    constexpr auto const& array = make_test_array<T, Dimension>::value0;

    // default
    {
      constexpr vector_type v{};
      for (usize i = 0; i < Dimension; ++i)
      {
        value_equal(v[i], T{0});
      }
    }

    // array
    {
      constexpr vector_type v{array};
      for (usize i = 0; i < Dimension; ++i)
      {
        value_equal(v[i], array[i]);
      }
    }

    // copy
    {
      constexpr vector_type a{array};
      constexpr vector_type b{a};
      vector_equal(a, b);
    }

    // move
    {
      constexpr vector_type a{array};
      constexpr vector_type b{std::move(a)};
      vector_equal(a, b);
    }

    // another type
    {
      constexpr vector_type                    v{array};
      constexpr vector<float, Dimension>       a{v};
      constexpr vector<double, Dimension>      b{v};
      constexpr vector<long double, Dimension> c{v};
      vector_equal(v, vector_type{a});
      vector_equal(v, vector_type{b});
      vector_equal(v, vector_type{c});
    }

    // initializer_list
    {
      constexpr vector_type v{0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      for (usize i = 0; i < Dimension; ++i)
      {
        value_equal(v[i], (i < 10 ? static_cast<T>(i * 10) : T{0}));
      }
    }
  } // namespace
};

TEST(vector_test, constructor) { tester<constructor_test>{}(); }

/******************************************************************************
 * operators
 ******************************************************************************/
template <typename T, pyrite::usize Dimension>
struct operator_eq_test
{
  void operator()()
  {
    using vector_type = vector<T, Dimension>;
    auto const& array = make_test_array<T, Dimension>::value0;

    vector_type a{array};
    vector_type b{array};

    ASSERT_TRUE(a == b);

    b[0] += static_cast<T>(1);
    ASSERT_FALSE(a == b);
  }
};

template <typename T, pyrite::usize Dimension>
struct operator_plus_eq_test
{
  void operator()()
  {
    using vector_type = vector<T, Dimension>;
    vector_type a{make_test_array<T, Dimension>::value0};
    vector_type b{make_test_array<T, Dimension>::value1};
    vector_type c;

    for (std::size_t i = 0; i < Dimension; ++i)
    {
      c[i] = a[i] + b[i];
    }

    a += b;
    vector_equal(a, c);
  }
};

template <typename T, pyrite::usize Dimension>
struct operator_minus_eq_test
{
  void operator()()
  {
    using vector_type = vector<T, Dimension>;

    vector_type a{make_test_array<T, Dimension>::value0};
    vector_type b{make_test_array<T, Dimension>::value1};
    vector_type c;

    for (std::size_t i = 0; i < Dimension; ++i)
    {
      c[i] = a[i] - b[i];
    }

    a -= b;
    vector_equal(a, c);
  }
};

template <typename T, pyrite::usize Dimension>
struct operator_mul_eq_test
{
  void operator()()
  {
    using vector_type = vector<T, Dimension>;

    vector_type a{make_test_array<T, Dimension>::value0};
    vector_type b{make_test_array<T, Dimension>::value1};
    vector_type c;
    vector_type d;
    T           scalar{42.2};

    for (std::size_t i = 0; i < Dimension; ++i)
    {
      c[i] = a[i] * b[i];
      d[i] = c[i] * scalar;
    }

    a *= b;
    vector_equal(a, c);
    c *= scalar;
    vector_equal(c, d);
  }
};

template <typename T, pyrite::usize Dimension>
struct operator_dev_eq_test
{
  void operator()()
  {
    using vector_type = vector<T, Dimension>;

    vector_type a{make_test_array<T, Dimension>::value0};
    vector_type b{make_test_array<T, Dimension>::value1};
    vector_type c;
    vector_type d;
    T           scalar{T{42.2}};

    for (std::size_t i = 0; i < Dimension; ++i)
    {
      c[i] = a[i] / b[i];
      d[i] = c[i] / scalar;
    }

    a /= b;
    vector_equal(a, c);
    c /= scalar;
    vector_equal(c, d);
  }
};

template <typename T, pyrite::usize Dimension>
struct operator_plus_test
{
  void operator()()
  {
    using vector_type = vector<T, Dimension>;

    constexpr vector_type a{make_test_array<T, Dimension>::value0};
    constexpr vector_type b{make_test_array<T, Dimension>::value1};
    vector_type           c{a};
    c += b;

    vector_equal(a + b, c);
  }
};

template <typename T, pyrite::usize Dimension>
struct operator_minus_test
{
  void operator()()
  {
    using vector_type = vector<T, Dimension>;

    constexpr vector_type a{make_test_array<T, Dimension>::value0};
    constexpr vector_type b{make_test_array<T, Dimension>::value1};
    vector_type           c{a};
    c -= b;

    vector_equal(a - b, c);
  }
};

template <typename T, pyrite::usize Dimension>
struct operator_mul_test
{
  void operator()()
  {
    using vector_type = vector<T, Dimension>;

    constexpr vector_type a{make_test_array<T, Dimension>::value0};
    constexpr vector_type b{make_test_array<T, Dimension>::value1};
    vector_type           c{a};
    vector_type           d{a};
    constexpr T           scalar{42};
    c *= b;
    d *= scalar;

    vector_equal(a * b, c);
    vector_equal(a * scalar, d);
  }
};

template <typename T, pyrite::usize Dimension>
struct operator_dev_test
{
  void operator()()
  {
    using vector_type = vector<T, Dimension>;

    constexpr vector_type a{make_test_array<T, Dimension>::value0};
    constexpr vector_type b{make_test_array<T, Dimension>::value1};
    vector_type           c{a};
    vector_type           d{a};
    constexpr T           scalar{42};
    c /= b;
    d /= scalar;

    vector_equal(a / b, c);
    vector_equal(a / scalar, d);
  }
};

template <typename T, pyrite::usize Dimension>
struct unary_operator_test
{
  void operator()()
  {
    using vector_type = vector<T, Dimension>;

    constexpr vector_type a{make_test_array<T, Dimension>::value0};
    vector_equal(+a, a);
    vector_equal(-a, a * T{-1});
  }
};

TEST(vector_test, operators)
{
  tester<operator_eq_test>{}();
  tester<operator_plus_eq_test>{}();
  tester<operator_minus_eq_test>{}();
  tester<operator_mul_eq_test>{}();
  tester<operator_dev_eq_test>{}();

  tester<operator_plus_test>{}();
  tester<operator_minus_test>{}();
  tester<operator_mul_test>{}();
  tester<operator_dev_test>{}();

  tester<unary_operator_test>{}();
}

TEST(vector_test, dot)
{
  using vector_t = vector<float, 3>;
  auto d         = dot(vector_t{0, 1, 2}, vector_t{0, 1, 2});
  EXPECT_FLOAT_EQ(d, 5.0f);
}
} // namespace
