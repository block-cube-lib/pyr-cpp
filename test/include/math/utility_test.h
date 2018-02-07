#ifndef TEST_INCLUDE_MATH_UTILITY_TEST_H
#define TEST_INCLUDE_MATH_UTILITY_TEST_H

#include <pyrite/math/utility.hpp>

#include "gtest/gtest.h"
#include <string>

inline namespace test
{
template <typename T>
class math_utility_test : public ::testing::Test
{
public:
  using value_type                  = T;
  static constexpr T near_abs_error = static_cast<T>(0.000001);

  static void equal(T a, T b)
  {
    if constexpr (std::is_same_v<T, float>)
    {
      EXPECT_FLOAT_EQ(a, b);
    }
    else if constexpr (std::is_same_v<T, double>)
    {
      EXPECT_DOUBLE_EQ(a, b);
    }
    else if constexpr (std::is_same_v<T, long double>)
    {
      EXPECT_DOUBLE_EQ(static_cast<double>(a), static_cast<double>(b));
    }
    else
    {
      EXPECT_EQ(a, b);
    }
  }

  static void near(T a, T b) { EXPECT_NEAR(a, b, near_abs_error); }

  template <typename F, typename IntType = int>
  static void loop(F test_func, IntType begin, IntType end, IntType step = 1)
  {
    for (IntType i = begin; i < end; i += step)
    {
      SCOPED_TRACE("i = " + std::to_string(i));
      test_func(i);
    }
  }

  template <typename F, typename IntType = int>
  static void loop2(F       test_func,
                    IntType begin1,
                    IntType end1,
                    IntType begin2,
                    IntType end2,
                    IntType step1 = 1,
                    IntType step2 = 1)
  {
    for (IntType i = begin1; i < end1; i += step1)
    {
      SCOPED_TRACE("i = " + std::to_string(i));
      for (IntType j = begin2; j < end2; j += step2)
      {
        SCOPED_TRACE("j = " + std::to_string(j));
        test_func(i, j);
      }
    }
  }
};
} // namespace test

#endif // TEST_INCLUDE_MATH_UTILITY_TEST_H
