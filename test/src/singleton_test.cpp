#include "gtest/gtest.h"

#include <atomic>
#include <thread>
#include <vector>

#include <pyrite/singleton.hpp>

namespace
{
class test_singleton : public pyrite::singleton<test_singleton>
{
  friend class pyrite::singleton_traits<test_singleton>;

private:
  test_singleton() { construct_count++; }

public:
  static std::atomic_int construct_count;
  std::atomic_int        value = 0;
};
std::atomic_int test_singleton::construct_count = 0;

TEST(singleton_test, instance)
{
  auto instance = test_singleton::instance();
  EXPECT_EQ(instance, test_singleton::instance());
}

TEST(singleton_test, instance_value)
{
  test_singleton::construct_count = 0;
  {
    auto instance = test_singleton::instance();
    EXPECT_EQ(instance->value, 0);
    EXPECT_EQ(test_singleton::construct_count, 1);

    instance->value++;
    EXPECT_EQ(instance->value, 1);
    EXPECT_EQ(test_singleton::construct_count, 1);
  }

  test_singleton::construct_count = 0;
  {
    auto instance = test_singleton::instance();
    EXPECT_EQ(instance->value, 0);
    EXPECT_EQ(test_singleton::construct_count, 1);
  }
}

TEST(singleton_test, thread)
{
  constexpr int                   thread_size{256};
  std::shared_ptr<test_singleton> instance{nullptr};
  std::vector<std::thread>        threads(thread_size);

  std::atomic_bool wait;

  test_singleton::construct_count = 0;
  for (auto&& t : threads)
  {
    t = std::thread([&]() {
      while (wait) {}
      instance = test_singleton::instance();
    });
  }

  wait = false;
  for (auto&& t : threads)
  {
    t.join();
  }

  EXPECT_EQ(test_singleton::construct_count, 1);
}
} // namespace

namespace
{
class test_singleton2 : public pyrite::singleton<test_singleton2>
{
  friend class pyrite::singleton_traits<test_singleton2>;

private:
  test_singleton2() {}
};
} // namespace

namespace pyrite
{
template <>
class singleton_traits<test_singleton2>
{
public:
  static test_singleton2* create()
  {
    new_count++;
    return new test_singleton2();
  }

  static void destroy(test_singleton2*& ptr)
  {
    delete_count++;
    pyrite::checked_delete(ptr);
  }

  static int new_count;
  static int delete_count;
};

int singleton_traits<test_singleton2>::new_count    = 0;
int singleton_traits<test_singleton2>::delete_count = 0;
} // namespace pyrite

namespace
{
TEST(singleton, singleton_traits)
{
  using traits         = pyrite::singleton_traits<test_singleton2>;
  traits::new_count    = 0;
  traits::delete_count = 0;
  EXPECT_EQ(traits::new_count, 0);
  EXPECT_EQ(traits::delete_count, 0);
  {
    auto instance = test_singleton2::instance();
    EXPECT_EQ(traits::new_count, 1);
    EXPECT_EQ(traits::delete_count, 0);
  }
  EXPECT_EQ(traits::new_count, 1);
  EXPECT_EQ(traits::delete_count, 1);
}
} // namespace
