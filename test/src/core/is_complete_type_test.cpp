//#include <pyrite/core/is_complete_type.hpp>
#include <pyrite/type_traits/is_complete_type.hpp>

#include "gtest/gtest.h"

class complete_type
{
};
class non_complete_type;
class will_complete_type;

using pyrite::type_traits::is_complete_type;
using pyrite::type_traits::is_complete_type_v;

TEST(is_complete_type_test, complete_type)
{
  EXPECT_TRUE(is_complete_type_v<complete_type>);
  EXPECT_TRUE(is_complete_type_v<int>);
  EXPECT_TRUE(is_complete_type_v<void*>);

  class inner_function_class
  {
  };
  EXPECT_TRUE(is_complete_type_v<inner_function_class>);
}

TEST(is_complete_type_test, non_complete_type)
{
  EXPECT_FALSE(is_complete_type_v<will_complete_type>);
  EXPECT_FALSE(is_complete_type_v<non_complete_type>);
  EXPECT_FALSE(is_complete_type_v<void>);

  class inner_function_class;
  EXPECT_FALSE(is_complete_type_v<inner_function_class>);
}

class will_complete_type
{
};

TEST(is_complete_type_test, will_complete_type)
{
  EXPECT_FALSE(is_complete_type_v<will_complete_type>);
}
