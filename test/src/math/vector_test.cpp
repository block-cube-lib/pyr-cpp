#include <pyrite/math/vector.hpp>

#include "gtest/gtest.h"

#include <iostream>
#include <type_traits>
#include <utility>
#include <string>

namespace pyrite::math
{
template <typename T, usize Dimension>
void PrintTo(vector<T, Dimension> const& v, ::std::ostream* os)
{
  for (usize i = 0; i < Dimension; ++i)
  {
    *os << v[i];
    if (i != Dimension - 1)
    {
      *os << ", ";
    }
  }
}
} // namespace pyrite::math

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
    SCOPED_TRACE("float");
    EXPECT_FLOAT_EQ(a, b);
  }
  else if constexpr (std::is_same_v<T, double>)
  {
    SCOPED_TRACE("double");
    EXPECT_DOUBLE_EQ(a, b);
  }
  else
  {
    SCOPED_TRACE("long double");
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

template <template <typename, usize> typename Func,
          typename Seq = std::make_index_sequence<20>>
struct tester;

template <template <typename, usize> typename Func, std::size_t... I>
struct tester<Func, std::index_sequence<I...>>
{
  void operator()()
  {
    (void)((call<float, I + 1>(), 0) + ...);
    (void)((call<double, I + 1>(), 0) + ...);
    (void)((call<long double, I + 1>(), 0) + ...);
  }

private:
  template <typename T, usize Dimension>
  void call()
  {
    SCOPED_TRACE("dimension = " + std::to_string(Dimension + 1));
    Func<T, Dimension>{}();
  }
};

template <typename T,
          usize Dimension,
          typename Sequence = std::make_index_sequence<Dimension>>
struct make_test_array;

template <typename T, usize Dimension, std::size_t... Index>
struct make_test_array<T, Dimension, std::index_sequence<Index...>>
{
  static constexpr T value0[Dimension]{static_cast<T>((Index + 1) * 1.1)...};
  static constexpr T value1[Dimension]{static_cast<T>((Index + 1) * 2.01)...};
  static constexpr T value2[Dimension]{static_cast<T>((Index + 1) * 3.2)...};
};

/******************************************************************************
 * constructors
 ******************************************************************************/
template <typename T, usize Dimension>
struct constructor_test
{
  void operator()()
  {
    using vector_type           = vector<T, Dimension>;
    constexpr auto const& array = make_test_array<T, Dimension>::value0;

    // default
    {
      SCOPED_TRACE("default");
      constexpr vector_type v{};
      for (usize i = 0; i < Dimension; ++i)
      {
        value_equal(v[i], T{0});
      }
    }

    // array
    {
      SCOPED_TRACE("array");
      constexpr vector_type v{array};
      for (usize i = 0; i < Dimension; ++i)
      {
        value_equal(v[i], array[i]);
      }
    }

    // copy
    {
      SCOPED_TRACE("copy");
      constexpr vector_type a{array};
      constexpr vector_type b{a};
      vector_equal(a, b);
    }

    // move
    {
      SCOPED_TRACE("move");
      constexpr vector_type a{array};
      constexpr vector_type b{std::move(a)};
      vector_equal(a, b);
    }

    // another type
    {
      SCOPED_TRACE("another type");
      constexpr vector_type                    v{array};
      constexpr vector<float, Dimension>       a{v};
      constexpr vector<double, Dimension>      b{v};
      constexpr vector<long double, Dimension> c{v};
      for(usize i = 0; i < Dimension; ++i)
      {
        value_equal(static_cast<float>(v[i]), a[i]);
        value_equal(static_cast<double>(v[i]), b[i]);
        value_equal(static_cast<long double>(v[i]), c[i]);
      }
    }

    // initializer_list
    {
      SCOPED_TRACE("initializer_list");
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
template <typename T, usize Dimension>
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

template <typename T, usize Dimension>
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

template <typename T, usize Dimension>
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

template <typename T, usize Dimension>
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

template <typename T, usize Dimension>
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

template <typename T, usize Dimension>
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

template <typename T, usize Dimension>
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

template <typename T, usize Dimension>
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

template <typename T, usize Dimension>
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

template <typename T, usize Dimension>
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

/******************************************************************************
 * member function
 ******************************************************************************/
template <typename T, usize Dimension>
struct dot_test
{
  using vector_t = vector<T, Dimension>;

  void operator()()
  {
    vector_t v1{make_test_array<T, Dimension>::value1};
    vector_t v2{make_test_array<T, Dimension>::value2};
    T        dot_value{0};
    for (usize i = 0; i < Dimension; i++)
    {
      dot_value += v1[i] * v2[i];
    }

    value_equal(v1.dot(v2), dot_value);
  }
};

TEST(vector_test, dot) { tester<dot_test>{}(); }

template <typename T, usize Dimension>
struct distance_test
{
  using vector_t = vector<T, Dimension>;

  void operator()()
  {
    vector_t v1{make_test_array<T, Dimension>::value1};
    vector_t v2{make_test_array<T, Dimension>::value2};

    T dist{0};
    for (usize i = 0; i < Dimension; i++)
    {
      dist += power(v1[i] - v2[i], 2);
    }

    value_equal(dist, v1.distance_squared(v2));
    value_equal(sqrt(dist), v1.distance(v2));
  }
};

TEST(vector_test, distance) { tester<distance_test>{}(); }

template <typename T, usize Dimension>
struct length_test
{
  using vector_t = vector<T, Dimension>;

  void operator()()
  {
    vector_t v{make_test_array<T, Dimension>::value1};

    T len{0};
    for (usize i = 0; i < Dimension; i++)
    {
      len += power(v[i], 2);
    }
    value_equal(len, v.length_squared());
    value_equal(sqrt(len), v.length());
  }
};

TEST(vector_test, length) { tester<length_test>{}(); }

template <typename T, usize Dimension>
struct normalize_test
{
  using vector_t = vector<T, Dimension>;

  void operator()()
  {
    // length == 0
    {
      vector_t v;
      vector_equal(v.normalized(), vector_t{});
      value_equal(v.length(), T{0});
      vector_equal(v.normalize(), vector_t{});
      value_equal(v.length(), T{0});
    }

    vector_t v1{make_test_array<T, Dimension>::value1};
    vector_t v2{make_test_array<T, Dimension>::value2};
    vector_equal(v1.normalized(), v1 / v1.length());
    value_equal(v1.normalized().length(), T{1});

    v1.normalize();
    value_equal(v1.length(), T{1});
    value_equal(v1.dot(v2), v2.length());
  }
};

TEST(vector_test, normalize) { tester<normalize_test>{}(); }
} // namespace
