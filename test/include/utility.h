#ifndef TEST_UTILITY_H
#define TEST_UTILITY_H

#include "gtest/gtest.h"

#include <string_view>
#include <type_traits>

inline namespace test
{
template <typename T>
void expect_equal(T const& a, T const& b, std::string_view scope = "")
{
  SCOPED_TRACE(scope);

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
} // namespace test

#endif // TEST_UTILITY_H
