/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_CORE_DETAIL_TYPE_HPP
#define PYRITE_CORE_DETAIL_TYPE_HPP

#include <type_traits>

#include <pyrite/core/mpl/type_list.hpp>
#include <pyrite/core/mpl/type_list/find_if.hpp>

namespace pyrite::core
{
namespace
{
using signed_list   = ::pyrite::core::mpl::type_list<signed int,
                                                   signed char,
                                                   signed short,
                                                   signed long,
                                                   signed long long>;
using unsigned_list = ::pyrite::core::mpl::type_list<unsigned int,
                                                     unsigned char,
                                                     unsigned short,
                                                     unsigned long,
                                                     unsigned long long>;
using floating_point_list =
  ::pyrite::core::mpl::type_list<float, double, long double>;

template <typename List, std::size_t Size>
struct find_from_size;

template <typename... Args, std::size_t Size>
struct find_from_size<::pyrite::core::mpl::type_list<Args...>, Size>
{
private:
  template <typename T>
  struct find_function : std::bool_constant<sizeof(T) == Size>
  {
  };

  using list = ::pyrite::core::mpl::type_list<Args...>;
  using opt  = ::pyrite::core::mpl::find_if_t<list, find_function>;
  static_assert(opt::has_type, "not found");

public:
  using type = typename opt::type;
};

template <typename List, std::size_t Size>
using find_from_size_t = typename find_from_size<List, Size>::type;

template <typename T>
constexpr auto max(T a, T b)
{
  return a < b ? b : a;
}
} // namespace

using i8  = find_from_size_t<signed_list, 1u>;
using i16 = find_from_size_t<signed_list, 2u>;
using i32 = find_from_size_t<signed_list, 4u>;
using i64 = find_from_size_t<signed_list, 8u>;

using u8  = find_from_size_t<unsigned_list, 1u>;
using u16 = find_from_size_t<unsigned_list, 2u>;
using u32 = find_from_size_t<unsigned_list, 4u>;
using u64 = find_from_size_t<unsigned_list, 8u>;

using f32 = find_from_size_t<floating_point_list, 4u>;
using f64 = find_from_size_t<floating_point_list, 8u>;

using isize =
  find_from_size_t<signed_list, max(sizeof(std::size_t), std::size_t{8u})>;
using usize =
  find_from_size_t<unsigned_list, max(sizeof(std::size_t), std::size_t{8u})>;

using iptr    = find_from_size_t<signed_list, sizeof(int*)>;
using uptr    = find_from_size_t<unsigned_list, sizeof(int*)>;
using ptrdiff = decltype(std::declval<int*>() - std::declval<int*>());
} // namespace pyrite::core

#endif // PYRITE_CORE_DETAIL_TYPE_HPP
