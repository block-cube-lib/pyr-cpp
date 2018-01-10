#include <pyrite/singleton.hpp>

#include "gtest/gtest.h"

namespace
{
class test_singleton : public pyrite::singleton<test_singleton>
{
  friend class pyrite::singleton_traits<test_singleton>;

private:
  test_singleton() {}

public:
  int value = 0;
};

int test_singleton2_new_count    = 0;
int test_singleton2_delete_count = 0;

class test_singleton2 : public pyrite::singleton<test_singleton2>
{
  friend class pyrite::singleton_traits<test_singleton2>;

private:
  test_singleton2() {}
};

TEST(singleton_test, instance)
{
  auto instance = test_singleton::instance();
  EXPECT_EQ(instance, test_singleton::instance());
}

TEST(singleton_test, instance_value)
{
  {
    auto instance = test_singleton::instance();
    EXPECT_EQ(instance->value, 0);
    instance->value++;
    EXPECT_EQ(instance->value, 1);
  }

  {
    auto instance = test_singleton::instance();
    EXPECT_EQ(instance->value, 0);
  }
}

TEST(singleton, singleton_traits)
{
  EXPECT_EQ(test_singleton2_new_count, 0);
  EXPECT_EQ(test_singleton2_delete_count, 0);
  {
    auto instance = test_singleton2::instance();
    EXPECT_EQ(test_singleton2_new_count, 1);
    EXPECT_EQ(test_singleton2_delete_count, 0);
  }
  EXPECT_EQ(test_singleton2_new_count, 1);
  EXPECT_EQ(test_singleton2_delete_count, 1);
}
} // namespace

namespace pyrite
{
template <>
class singleton_traits<test_singleton2>
{
public:
  static test_singleton2* create()
  {
    ::test_singleton2_new_count++;
    return new test_singleton2();
  }

  static void destroy(test_singleton2*& ptr)
  {
    ::test_singleton2_delete_count++;
    pyrite::checked_delete(ptr);
  }
};
} // namespace pyrite
