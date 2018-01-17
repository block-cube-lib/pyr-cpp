#include "gtest/gtest.h"

#include <algorithm>
#include <limits>
#include <vector>

#include <pyrite/core/type.hpp>
#include <pyrite/random.hpp>

namespace
{

TEST(random_test, construct)
{
  [[maybe_unused]] pyrite::random r0;
  [[maybe_unused]] pyrite::random r1 { 0 };
  [[maybe_unused]] pyrite::random r2 { r1 };
  [[maybe_unused]] pyrite::random r3 { std::move(r2) };
}

TEST(random_test, next)
{
  pyrite::random random;

  {
    constexpr int min = std::numeric_limits<int>::min();
    constexpr int max = std::numeric_limits<int>::max();
    for (int i = 0; i < 10000; ++i)
    {
      auto const value = random.next<int>();
      EXPECT_LE(value, max);
      EXPECT_GE(value, min);
    }
  }
  {
    constexpr double min = 0.0;
    constexpr double max = 1.0;
    for (int i = 0; i < 10000; ++i)
    {
      auto const value = random.next<double>();
      EXPECT_LE(value, max);
      EXPECT_GE(value, min);
    }
  }
}

TEST(random_test, next_min_max)
{
  pyrite::random random;

  {
    constexpr int min = 1;
    constexpr int max = 42;
    for (int i = 0; i < 10000; ++i)
    {
      auto const value = random.next<int>(min, max);
      EXPECT_LE(value, max);
      EXPECT_GE(value, min);
    }
  }
  {
    constexpr double min = 1.0;
    constexpr double max = 1.1;
    for (int i = 0; i < 10000; ++i)
    {
      auto const value = random.next<double>(min, max);
      EXPECT_LE(value, max);
      EXPECT_GE(value, min);
    }
  }
}

TEST(random_test, seed)
{
  pyrite::random random{42u};
  EXPECT_EQ(random.seed(), 42u);
}

void discard_test(unsigned int discard_count)
{
  pyrite::random random1{0};
  for (unsigned int i = 0; i < discard_count; ++i)
  {
    [[maybe_unused]] auto const dummy = random1.next<int>();
  }

  pyrite::random random2{0};
  random2.discard(discard_count);

  EXPECT_EQ(random1.next<int>(), random2.next<int>());
}

TEST(random_test, discard)
{
  for (int i = 0; i < 100; ++i)
  {
    discard_test(i);
  }
}

namespace reset_test
{
std::vector<pyrite::u32> v1{500};
std::vector<pyrite::u32> v2{500};

auto make_random_vector(pyrite::random& random, std::vector<pyrite::u32>& v)
{
  std::generate(begin(v), end(v), [&]() { return random.next<pyrite::u32>(); });
}

TEST(random_test, reset)
{
  pyrite::random random;
  make_random_vector(random, v1);
  random.reset();
  make_random_vector(random, v2);
  EXPECT_EQ(v1, v2);
}

TEST(random_test, reset_seed)
{
  pyrite::random random;
  random.discard(42);
  auto const seed = random.seed();
  random.reset(seed);
  make_random_vector(random, v1);
  random.reset(seed);
  make_random_vector(random, v2);
  EXPECT_EQ(v1, v2);
}

TEST(random_test, reset_state)
{
  pyrite::random random;
  auto const     state = random.state();
  make_random_vector(random, v1);
  auto const after_state = random.state();

  random.discard(42);
  random.reset(state);
  make_random_vector(random, v2);

  EXPECT_EQ(v1, v2);
  EXPECT_NE(state, after_state);
  EXPECT_EQ(after_state, random.state());
}
} // namespace reset_test

TEST(random_test, copy)
{
  pyrite::random random1;

  for (int i = 0; i < 10; ++i)
  {
    random1.discard(i);
    pyrite::random random2{random1};
    EXPECT_EQ(random1, random2);
  }

  for (int i = 0; i < 10; ++i)
  {
    random1.discard(i);
    pyrite::random random2;
    random2 = random1;
    EXPECT_EQ(random1, random2);
  }
}

TEST(random_test, move)
{
  for (int i = 0; i < 10; ++i)
  {
    pyrite::random random1;
    random1.discard(i);
    auto const state = random1.state();
    pyrite::random random2{std::move(random1)};
    EXPECT_EQ(state, random2.state());
  }

  for (int i = 0; i < 10; ++i)
  {
    pyrite::random random1;
    random1.discard(i);
    auto const state = random1.state();
    pyrite::random random2;
    random2 = std::move(random1);
    EXPECT_EQ(state, random2.state());
  }
}
} // namespace
