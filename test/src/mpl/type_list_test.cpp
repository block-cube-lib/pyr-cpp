#include <pyrite/mpl/type_list.hpp>
#include <pyrite/mpl/type_optional.hpp>

#include "gtest/gtest.h"

#include <type_traits>


namespace
{

using namespace pyrite::mpl;
TEST(type_list_test, size)
{
  EXPECT_EQ((type_list<>::size), 0u);
  EXPECT_EQ((type_list<int>::size), 1u);
  EXPECT_EQ((type_list<int, float>::size), 2u);
  EXPECT_EQ((type_list<int, float, char>::size), 3u);
}

TEST(type_list_test, is_type_list)
{
  EXPECT_TRUE(is_type_list_v<type_list<>>);
  EXPECT_TRUE(is_type_list_v<type_list<int>>);
  EXPECT_TRUE(is_type_list_v<type_list<type_list<>>>);
  EXPECT_FALSE(is_type_list_v<int>);
  EXPECT_FALSE(is_type_list_v<null_type_optional>);
  EXPECT_FALSE(is_type_list_v<type_optional<type_list<>>>);
}

template <typename... L, typename... R>
void check_operator_plus(type_list<L...> l, type_list<R...> r)
{
  ::testing::StaticAssertTypeEq<decltype(l + r), type_list<L..., R...>>();
}

TEST(type_list_test, operators)
{
  check_operator_plus(type_list<>{}, type_list<>{});
  check_operator_plus(type_list<int>{}, type_list<>{});
  check_operator_plus(type_list<>{}, type_list<int>{});
  check_operator_plus(type_list<double>{}, type_list<int>{});
}

template <typename List, typename Optional>
void head_check()
{
  using head_type = head_t<List>;
  ::testing::StaticAssertTypeEq<head_type, Optional>();
}

TEST(type_list_test, head)
{
  head_check<type_list<>, null_type_optional>();
  head_check<type_list<int>, type_optional<int>>();
  head_check<type_list<char, void*>, type_optional<char>>();
  head_check<type_list<int, float, double>, type_optional<int>>();
  head_check<type_list<signed char const* const&, void>,
             type_optional<signed char const* const&>>();
}

template <template <typename> typename F,
          typename BeforeList,
          typename ResultList>
void filter_check()
{
  ::testing::StaticAssertTypeEq<filter_t<BeforeList, F>, ResultList>();
}

TEST(type_list_test, filter)
{
  using ushort = unsigned short;
  using list   = type_list<int,
                         int const,
                         int volatile,
                         int*,
                         int&,
                         ushort,
                         ushort const,
                         ushort volatile,
                         ushort*,
                         ushort&,
                         float,
                         float const,
                         float volatile,
                         float*,
                         float&>;

  filter_check<std::is_unsigned,
               list,
               type_list<ushort, ushort const, ushort volatile>>();
  filter_check<std::is_floating_point,
               list,
               type_list<float, float const, float volatile>>();
  filter_check<std::is_reference, list, type_list<int&, ushort&, float&>>();
  filter_check<std::is_const,
               list,
               type_list<int const, ushort const, float const>>();
}

template <typename List,
          template <typename> typename F,
          typename ResultOptional>
void find_if_check()
{
  using result = find_if_t<List, F>;
  ::testing::StaticAssertTypeEq<result, ResultOptional>();
}

TEST(type_list_test, find_if)
{
  using ushort = unsigned short;
  using list   = type_list<int,
                         int&,
                         ushort,
                         ushort volatile,
                         ushort*,
                         ushort&,
                         float const,
                         float*>;

  find_if_check<list, std::is_integral, type_optional<int>>();
  find_if_check<list, std::is_unsigned, type_optional<ushort>>();
  find_if_check<list, std::is_reference, type_optional<int&>>();
  find_if_check<list, std::is_pointer, type_optional<ushort*>>();
  find_if_check<list, std::is_volatile, type_optional<ushort volatile>>();
  find_if_check<list, std::is_const, type_optional<float const>>();
  find_if_check<list, std::is_void, null_type_optional>();
}

TEST(type_list_test, tail)
{
  ::testing::StaticAssertTypeEq<tail_t<type_list<>>, type_list<>>();
  ::testing::StaticAssertTypeEq<tail_t<type_list<int>>, type_list<>>();
  ::testing::StaticAssertTypeEq<tail_t<type_list<char, float>>,
                                type_list<float>>();
  ::testing::StaticAssertTypeEq<tail_t<type_list<float, int, int>>,
                                type_list<int, int>>();
  ::testing::StaticAssertTypeEq<tail_t<type_list<int const*, double const>>,
                                type_list<double const>>();
}

TEST(type_list_test, at)
{
  using list = type_list<int, char, float, double, char const, std::nullptr_t>;
  ::testing::StaticAssertTypeEq<at_t<list, 0>, int>();
  ::testing::StaticAssertTypeEq<at_t<list, 1>, char>();
  ::testing::StaticAssertTypeEq<at_t<list, 2>, float>();
  ::testing::StaticAssertTypeEq<at_t<list, 3>, double>();
  ::testing::StaticAssertTypeEq<at_t<list, 4>, char const>();
  ::testing::StaticAssertTypeEq<at_t<list, 5>, std::nullptr_t>();
}

template <typename ListL, typename ListR>
void join_check()
{
  ::testing::StaticAssertTypeEq<join_t<ListL, ListR>,
                                decltype(ListL{} + ListR{})>();
}

TEST(type_list_test, join)
{
  join_check<type_list<>, type_list<>>();
  join_check<type_list<int>, type_list<>>();
  join_check<type_list<>, type_list<int>>();
  join_check<type_list<void>, type_list<void*>>();
  join_check<type_list<void, float>, type_list<char, short>>();
}

template <typename List, typename PushType, typename ResultList>
void push_back_check()
{
  using result = push_back_t<List, PushType>;
  ::testing::StaticAssertTypeEq<result, ResultList>();
}

TEST(type_list_test, push_back)
{
  push_back_check<type_list<>, int, type_list<int>>();
  push_back_check<type_list<int>, float, type_list<int, float>>();
  push_back_check<type_list<char, void>, int, type_list<char, void, int>>();
}

template <typename List, typename PushType, typename ResultList>
void push_front_check()
{
  using result = push_front_t<List, PushType>;
  ::testing::StaticAssertTypeEq<result, ResultList>();
}

TEST(type_list_test, push_front)
{
  push_front_check<type_list<>, int, type_list<int>>();
  push_front_check<type_list<int>, float, type_list<float, int>>();
  push_front_check<type_list<char, void>, int, type_list<int, char, void>>();
}

TEST(type_list_test, all_of)
{
  EXPECT_TRUE((all_of_v<type_list<>, std::is_integral>));
  EXPECT_TRUE((all_of_v<type_list<int>, std::is_integral>));
  EXPECT_TRUE((all_of_v<type_list<int, short>, std::is_integral>));
  EXPECT_FALSE((all_of_v<type_list<double, int>, std::is_integral>));
  EXPECT_FALSE((all_of_v<type_list<double, float>, std::is_integral>));
}

TEST(type_list_test, any_of)
{
  EXPECT_TRUE((any_of_v<type_list<>, std::is_integral>));
  EXPECT_TRUE((any_of_v<type_list<long>, std::is_integral>));
  EXPECT_TRUE((any_of_v<type_list<double, int>, std::is_floating_point>));
  EXPECT_TRUE((any_of_v<type_list<int, double, int>, std::is_floating_point>));
  EXPECT_FALSE((any_of_v<type_list<long, int>, std::is_floating_point>));
}

TEST(type_list_test, none_of)
{
  EXPECT_TRUE((none_of_v<type_list<>, std::is_integral>));
  EXPECT_TRUE((none_of_v<type_list<double>, std::is_integral>));
  EXPECT_TRUE((none_of_v<type_list<float, double>, std::is_integral>));
  EXPECT_TRUE((none_of_v<type_list<int, char, short>, std::is_floating_point>));
  EXPECT_FALSE((none_of_v<type_list<long, float>, std::is_floating_point>));
  EXPECT_FALSE((none_of_v<type_list<float, float>, std::is_floating_point>));
}

template <typename List, template <typename> typename F, typename ResultList>
void transform_check()
{
  using result = transform_t<List, F>;
  ::testing::StaticAssertTypeEq<result, ResultList>();
}

TEST(type_list_test, transform)
{
  transform_check<type_list<>, std::add_pointer, type_list<>>();
  transform_check<type_list<int>, std::add_pointer, type_list<int*>>();
  transform_check<type_list<int, char>,
                  std::add_pointer,
                  type_list<int*, char*>>();
}

TEST(type_list_test, reverse)
{
  using _1 = int;
  using _2 = char;
  using _3 = short;
  ::testing::StaticAssertTypeEq<reverse_t<type_list<>>, type_list<>>();
  ::testing::StaticAssertTypeEq<reverse_t<type_list<_1>>, type_list<_1>>();
  ::testing::StaticAssertTypeEq<reverse_t<type_list<_1, _2>>,
                                type_list<_2, _1>>();
  ::testing::StaticAssertTypeEq<reverse_t<type_list<_1, _2, _3>>,
                                type_list<_3, _2, _1>>();
}

TEST(type_list_test, make_type_list)
{
  using t = int;
  ::testing::StaticAssertTypeEq<make_type_list<t, 0>, type_list<>>();
  ::testing::StaticAssertTypeEq<make_type_list<t, 1>, type_list<t>>();
  ::testing::StaticAssertTypeEq<make_type_list<t, 2>, type_list<t, t>>();
  ::testing::StaticAssertTypeEq<make_type_list<t, 3>, type_list<t, t, t>>();
  ::testing::StaticAssertTypeEq<make_type_list<t, 4>, type_list<t, t, t, t>>();

  EXPECT_EQ((make_type_list<t, 2000>::size), 2000u);
}
} // namespace
