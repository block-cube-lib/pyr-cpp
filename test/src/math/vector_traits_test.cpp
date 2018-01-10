#include "gtest/gtest.h"

#include <utility>
#include <array>

#include <pyrite/config/type.hpp>
#include <pyrite/math/vector_traits.hpp>
#include <pyrite/math/vector_traits/array.hpp>

namespace
{
using pyrite::math::vector_traits;

struct vector
{
  using value_type                         = float;
  static constexpr pyrite::usize dimension = 3u;

  constexpr float& operator[](std::size_t const& index) { return value[index]; }

  constexpr float const& operator[](std::size_t const& index) const
  {
    return value[index];
  }

public:
  float value[3]{0.0f, 0.0f, 0.0f};
};

template <typename T>
void vector_type_check()
{
  ::testing::StaticAssertTypeEq<T, typename vector_traits<T>::vector_type>();
}

template <typename T, pyrite::usize dimension>
void dimension_check()
{
  ASSERT_EQ(dimension, vector_traits<T>::dimension);
}

template <typename T, typename ValueType>
void value_type_check()
{
  ::testing::StaticAssertTypeEq<ValueType,
                                typename vector_traits<T>::value_type>();
}

template <typename T>
void at_check(T v)
{
  for (auto i = 0u; i < vector_traits<T>::dimension; ++i)
  {
    EXPECT_EQ(std::addressof(v[i]),
              std::addressof(vector_traits<T>::at(v, i)));
  }
}

TEST(vector_traits_test, alias)
{
  vector_type_check<vector>();
  value_type_check<vector, float>();
}

TEST(vector_traits_test, constant) { dimension_check<vector, 3u>(); }

TEST(vector_traits_test, at)
{
  vector v = {{1.5f, 2.0f, 4.5f}};
  at_check(v);
  at_check(std::as_const(v));
}

TEST(vector_traits_std_array_test, alias)
{
  vector_type_check<std::array<int, 4>>();
  value_type_check<std::array<int, 4>, int>();

  vector_type_check<std::array<double, 8>>();
  value_type_check<std::array<double, 8>, double>();

  vector_type_check<std::array<char, 200>>();
  value_type_check<std::array<char, 200>, char>();
}

template <pyrite::usize Max>
void std_array_dimension_check()
{
  if constexpr(Max != 0)
  {
    dimension_check<std::array<double, Max>, Max>();
    std_array_dimension_check<Max - 1>();
  }
}

TEST(vector_traits_std_array_test, constant)
{
  std_array_dimension_check<500u>();
}

TEST(vector_traits_std_array_test, at)
{
  std::array<float, 500> v = {{0.0f}};
  at_check(v);
  at_check(std::as_const(v));
}
} // namespace
