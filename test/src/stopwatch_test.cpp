#include <chrono>
#include <thread>
#include <utility>

#include <pyrite/stopwatch.hpp>

#include "gtest/gtest.h"

using pyrite::stopwatch;

TEST(stopwatch_test, construct)
{
  stopwatch s;
  EXPECT_TRUE(s.is_running());
}

TEST(stopwatch_test, reset)
{
  stopwatch s;
  s.reset();
  EXPECT_FALSE(s.is_running());
}

TEST(stopwatch_test, start)
{
  stopwatch s;
  s.reset();
  s.start();
  EXPECT_TRUE(s.is_running());
}

TEST(stopwatch_test, stop)
{
  stopwatch s;
  s.stop();
  EXPECT_FALSE(s.is_running());
}

TEST(stopwatch_test, restart)
{
  stopwatch s;
  s.stop();
  EXPECT_FALSE(s.is_running());
  s.restart();
  EXPECT_TRUE(s.is_running());
}

TEST(stopwatch_test, elapsed)
{
  using namespace std::chrono_literals;
  stopwatch sw;
  std::this_thread::sleep_for(0.1s);
  EXPECT_GE(sw.elapsed_seconds<double>(), 0.1);

  sw.reset();
  EXPECT_DOUBLE_EQ(sw.elapsed_seconds<double>(), 0.0);

  sw.start();
  std::this_thread::sleep_for(0.5s);
  EXPECT_GE(sw.elapsed_seconds<double>(), 0.5);

  sw.stop();
  auto const elapsed = sw.elapsed_seconds<double>();
  std::this_thread::sleep_for(0.1s);
  EXPECT_DOUBLE_EQ(sw.elapsed_seconds<double>(), elapsed);

  sw.restart();
  std::this_thread::sleep_for(0.1s);
  EXPECT_GE(sw.elapsed_seconds<double>(), 0.1);
  EXPECT_LE(sw.elapsed_seconds<double>(), 0.11);

  sw.stop();
  EXPECT_DOUBLE_EQ(sw.elapsed_seconds<double>(),
                   sw.elapsed_milliseconds<double>() / 1000);
}

void same_check(stopwatch const& sw, bool is_running, double elapsed_seconds)
{
  ASSERT_EQ(sw.is_running(), is_running);
  ASSERT_DOUBLE_EQ(sw.elapsed_seconds<double>(), elapsed_seconds);
}

void same_check(stopwatch const& sw1, stopwatch const& sw2)
{
  ASSERT_EQ(sw1.is_running(), sw2.is_running());
  ASSERT_DOUBLE_EQ(sw1.elapsed_seconds<double>(),
                   sw2.elapsed_seconds<double>());
}

TEST(stopwatch_test, copy)
{
  using namespace std::chrono_literals;

  stopwatch sw1;
  std::this_thread::sleep_for(0.1s);

  sw1.stop();
  stopwatch sw2{sw1};

  ASSERT_NO_FATAL_FAILURE(same_check(sw1, sw2));

  sw1.start();
  std::this_thread::sleep_for(0.1s);
  EXPECT_NE(sw1.is_running(), sw2.is_running());
  EXPECT_NE(sw1.elapsed_seconds<double>(), sw2.elapsed_seconds<double>());

  sw1.stop();
  sw2 = sw1;
  ASSERT_NO_FATAL_FAILURE(same_check(sw1, sw2));
}

TEST(stopwatch_test, move)
{
  using namespace std::chrono_literals;

  stopwatch sw1;
  stopwatch sw2{std::move(sw1)};
  EXPECT_TRUE(sw2.is_running());

  std::this_thread::sleep_for(0.1s);
  sw2.stop();
  auto const elapsed = sw2.elapsed_seconds<double>();

  sw1 = std::move(sw2);
  ASSERT_NO_FATAL_FAILURE(same_check(sw1, false, elapsed));
}
