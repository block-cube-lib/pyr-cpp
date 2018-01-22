#include "gtest/gtest.h"

#include <type_traits>

//#include <pyrite/core/type_list.hpp>
#include <pyrite/mpl/type_holder.hpp>
#include <pyrite/mpl/type_list.hpp>

using ::pyrite::mpl::type_holder;
using ::pyrite::mpl::null_type_holder;
using ::pyrite::mpl::type_list;
using ::pyrite::mpl::make_type_list;

TEST(type_list_test, size)
{
  EXPECT_EQ((type_list<>::size), 0u);
  EXPECT_EQ((type_list<int>::size), 1u);
  EXPECT_EQ((type_list<int, float>::size), 2u);
  EXPECT_EQ((type_list<int, float, char>::size), 3u);
}

TEST(type_list_test, head)
{
  ::testing::StaticAssertTypeEq<type_list<>::head, null_type_holder>();
  ::testing::StaticAssertTypeEq<type_list<int>::head, type_holder<int>>();
  ::testing::StaticAssertTypeEq<type_list<char, float>::head,
                                type_holder<char>>();
  ::testing::StaticAssertTypeEq<type_list<float, int, int>::head,
                                type_holder<float>>();
  ::testing::StaticAssertTypeEq<type_list<int const*, double const>::head,
                                type_holder<int const*>>();
}

TEST(type_list_test, tail)
{
  ::testing::StaticAssertTypeEq<type_list<>::tail, type_list<>>();
  ::testing::StaticAssertTypeEq<type_list<int>::tail, type_list<>>();
  ::testing::StaticAssertTypeEq<type_list<char, float>::tail,
                                type_list<float>>();
  ::testing::StaticAssertTypeEq<type_list<float, int, int>::tail,
                                type_list<int, int>>();
  ::testing::StaticAssertTypeEq<type_list<int const*, double const>::tail,
                                type_list<double const>>();
}

TEST(type_list_test, at)
{
  using list = type_list<int, char, float, double, char const, std::nullptr_t>;
  ::testing::StaticAssertTypeEq<list::at<0>, int>();
  ::testing::StaticAssertTypeEq<list::at<1>, char>();
  ::testing::StaticAssertTypeEq<list::at<2>, float>();
  ::testing::StaticAssertTypeEq<list::at<3>, double>();
  ::testing::StaticAssertTypeEq<list::at<4>, char const>();
  ::testing::StaticAssertTypeEq<list::at<5>, std::nullptr_t>();
}

TEST(type_list_test, join)
{
  {
    using list1 = type_list<>;
    using list2 = type_list<>;
    ::testing::StaticAssertTypeEq<list1::join<list2>, type_list<>>();
  }

  {
    using list   = type_list<int>;
    using result = list::join<list>::join<list>::join<list>;
    ::testing::StaticAssertTypeEq<result, type_list<int, int, int, int>>();

    // list::join<int>; // compile error
  }
}

TEST(type_list_test, push_back)
{
  using empty = type_list<>;
  using list1 = empty::push_back<int>;
  using list2 = list1::push_back<int>;
  using list3 = list2::push_back<char>;
  using list4 = list3::push_back<list1>;

  ::testing::StaticAssertTypeEq<list1, type_list<int>>();
  ::testing::StaticAssertTypeEq<list2, type_list<int, int>>();
  ::testing::StaticAssertTypeEq<list3, type_list<int, int, char>>();
  ::testing::StaticAssertTypeEq<list4, type_list<int, int, char, list1>>();
}

TEST(type_list_test, push_front)
{
  using empty = type_list<>;
  using list1 = empty::push_front<int>;
  using list2 = list1::push_front<int>;
  using list3 = list2::push_front<char>;
  using list4 = list3::push_front<list1>;

  ::testing::StaticAssertTypeEq<list1, type_list<int>>();
  ::testing::StaticAssertTypeEq<list2, type_list<int, int>>();
  ::testing::StaticAssertTypeEq<list3, type_list<char, int, int>>();
  ::testing::StaticAssertTypeEq<list4, type_list<list1, char, int, int>>();
}

TEST(type_list_test, all_of)
{
  {
    using list = type_list<long, short>;
    EXPECT_TRUE(list::all_of<std::is_integral>);
  }

  {
    using list = type_list<double, float, long double>;
    EXPECT_TRUE(list::all_of<std::is_floating_point>);
  }

  {
    using list = type_list<int, float, long double>;
    EXPECT_FALSE(list::all_of<std::is_floating_point>);
  }

  {
    using list = type_list<>;
    EXPECT_TRUE(list::all_of<std::is_floating_point>);
  }
}

TEST(type_list_test, any_of)
{
  {
    using list = type_list<long, double>;
    EXPECT_TRUE(list::any_of<std::is_integral>);
  }

  {
    using list = type_list<double, double, double, int>;
    EXPECT_TRUE(list::any_of<std::is_floating_point>);
  }

  {
    using list = type_list<int, long, short>;
    EXPECT_FALSE(list::any_of<std::is_floating_point>);
  }

  {
    using list = type_list<>;
    EXPECT_TRUE(list::any_of<std::is_floating_point>);
  }
}

TEST(type_list_test, none_of)
{
  {
    using list = type_list<void, void>;
    EXPECT_TRUE(list::none_of<std::is_integral>);
  }

  {
    using list = type_list<int, void, short>;
    EXPECT_TRUE(list::none_of<std::is_floating_point>);
  }

  {
    using list = type_list<int, long, float>;
    EXPECT_FALSE(list::none_of<std::is_floating_point>);
  }

  {
    using list = type_list<>;
    EXPECT_TRUE(list::none_of<std::is_floating_point>);
  }
}

TEST(type_list_test, transform)
{
  {
    using list = type_list<>::transform<std::add_const>;
    ::testing::StaticAssertTypeEq<list, type_list<>>();
  }
  {
    using list = type_list<int>::transform<std::add_const>;
    ::testing::StaticAssertTypeEq<list, type_list<int const>>();
  }
  {
    using list = type_list<int, void>::transform<std::add_pointer>;
    ::testing::StaticAssertTypeEq<list, type_list<int*, void*>>();
  }
}

TEST(type_list_test, filter)
{
  using list = type_list<signed char,
                         double,
                         char*,
                         short,
                         unsigned long,
                         float,
                         void*,
                         long double>;

  {
    using result = type_list<signed char, short, unsigned long>;
    ::testing::StaticAssertTypeEq<list::filter<std::is_integral>, result>();
  }
  {
    using result = type_list<double, float, long double>;
    ::testing::StaticAssertTypeEq<list::filter<std::is_floating_point>,
                                  result>();
  }
  {
    using result = type_list<char*, void*>;
    ::testing::StaticAssertTypeEq<list::filter<std::is_pointer>, result>();
  }
}

TEST(type_list_test, find_if)
{
  using list = type_list<void,
                         float,
                         unsigned char,
                         long volatile,
                         short,
                         int,
                         double const>;
  ::testing::StaticAssertTypeEq<list::find_if<std::is_pointer>,
                                null_type_holder>();
  ::testing::StaticAssertTypeEq<list::find_if<std::is_void>,
                                type_holder<void>>();
  ::testing::StaticAssertTypeEq<list::find_if<std::is_floating_point>,
                                type_holder<float>>();
  ::testing::StaticAssertTypeEq<list::find_if<std::is_integral>,
                                type_holder<unsigned char>>();
  ::testing::StaticAssertTypeEq<list::find_if<std::is_volatile>,
                                type_holder<long volatile>>();
  ::testing::StaticAssertTypeEq<list::find_if<std::is_const>,
                                type_holder<double const>>();
}

TEST(type_list_test, reverse)
{
}

TEST(type_list_test, make_type_list)
{
  {
    using list = make_type_list<int, 0>;
    ::testing::StaticAssertTypeEq<list, type_list<>>();
  }
  {
    using list = make_type_list<int, 1>;
    ::testing::StaticAssertTypeEq<list, type_list<int>>();
  }
  {
    using list = make_type_list<int, 2>;
    ::testing::StaticAssertTypeEq<list, type_list<int, int>>();
  }
  {
    using list = make_type_list<int, 3>;
    ::testing::StaticAssertTypeEq<list, type_list<int, int, int>>();
  }
  {
    using list = make_type_list<int, 4>;
    ::testing::StaticAssertTypeEq<list, type_list<int, int, int, int>>();
  }
  {
    using list = make_type_list<int, 1023>;
    EXPECT_EQ(list::size, 1023u);
  }
  {
    using list = make_type_list<int, 2000>;
    EXPECT_EQ(list::size, 2000u);
  }
  {
    using list = make_type_list<int, 2001>;
    EXPECT_EQ(list::size, 2001u);
  }
}
