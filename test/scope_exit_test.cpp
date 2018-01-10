#include <pyrite/scope_exit.hpp>

#include "gtest/gtest.h"

namespace
{
static constexpr int default_value          = 1;
static constexpr int function_result        = 1;
static constexpr int function_object_result = 2;
static constexpr int lambda_result          = 3;
int                  value                  = 0;

void function() { value = function_result; }

struct function_object
{
  void operator()() { value = function_object_result; }
};

TEST(scope_exit_test, function)
{
  value = default_value;
  EXPECT_EQ(value, default_value);
  {
    [[maybe_unused]] auto se = pyrite::make_scope_exit(&function);
  }
  EXPECT_EQ(value, function_result);
}

TEST(scope_exit_test, function_object)
{
  value = default_value;
  EXPECT_EQ(value, default_value);
  {
    [[maybe_unused]] auto se = pyrite::make_scope_exit(function_object());
  }
  EXPECT_EQ(value, function_object_result);
}

TEST(scope_exit_test, lambda)
{
  value = default_value;
  EXPECT_EQ(value, default_value);
  {
    [[maybe_unused]] auto se =
      pyrite::make_scope_exit([]() { value = lambda_result; });
  }
  EXPECT_EQ(value, lambda_result);
}

TEST(scope_exit_test, nullptr)
{
  value = default_value;
  EXPECT_EQ(value, default_value);
  {
    [[maybe_unused]] pyrite::scope_exit<decltype(&function)> se(nullptr);
  }
  EXPECT_EQ(value, default_value);
}
} // namespace
