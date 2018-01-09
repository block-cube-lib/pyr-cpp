#include <pyrite/core/void_t.hpp>

#include "gtest/gtest.h"

TEST(void_t_test, default_test)
{
  using namespace pyrite;
  ::testing::StaticAssertTypeEq<void, void_t<>>();
  ::testing::StaticAssertTypeEq<void, void_t<int>>();
  ::testing::StaticAssertTypeEq<void, void_t<int, char>>();
  ::testing::StaticAssertTypeEq<void, void_t<int, float>>();
  ::testing::StaticAssertTypeEq<void, void_t<void_t<>>>();
  ::testing::StaticAssertTypeEq<void, void_t<void_t<int>>>();
  ::testing::StaticAssertTypeEq<void, void_t<std::nullptr_t>>();
}
