#ifndef PYRITE_CONFIG_TYPE_HPP
#define PYRITE_CONFIG_TYPE_HPP

/**
 * @file
 * @brief     Define types
 *
 * @date      2017/01/22 Create.
 *
 * @author    block
 *
 * @copyrite  2017 block (c)copyrite add rights reserved.
 */

#if defined( CHAR_BIT )
static_assert( CHAR_BIT == 8, "not support." );
#else
static_assert( false, "not support." );
#endif

namespace pyrite
{
namespace _type_impl
{
template <typename... Args>
struct type_list;

template <typename Head, typename... Tail>
struct type_list<Head, Tail...>
{
  using head = Head;
  using tail = type_list<Tail...>;
};

template <typename T>
struct is_empty_list
{
  static constexpr bool value = false;
};

template <>
struct is_empty_list<type_list<>>
{
  static constexpr bool value = true;
};

template <bool Cond, typename Then, typename Else>
struct conditional;

template <typename Then, typename Else>
struct conditional<true, Then, Else>
{
  using type = Then;
};
template <typename Then, typename Else>
struct conditional<false, Then, Else>
{
  using type = Else;
};

template <typename List, unsigned long long Size>
struct find_size_type
{
  using head = typename List::head;
  using tail = typename List::tail;

  using type = typename conditional<sizeof( head ) == Size,
                                    head,
                                    typename tail::head>::type;
};

template <typename List, unsigned long long Size>
using find_size_type_t = typename find_size_type<List, Size>::type;

using signed_list = type_list<signed int,
                              signed char,
                              signed short,
                              signed long,
                              signed long long>;
using unsigned_list = type_list<unsigned int,
                                unsigned char,
                                unsigned short,
                                unsigned long,
                                unsigned long long>;
using floating_point_list = type_list<float, double, long double>;

using i8  = find_size_type_t<signed_list, 1>;
using i16 = find_size_type_t<signed_list, 2>;
using i32 = find_size_type_t<signed_list, 4>;
using i64 = find_size_type_t<signed_list, 8>;

using u8  = find_size_type_t<unsigned_list, 1>;
using u16 = find_size_type_t<unsigned_list, 2>;
using u32 = find_size_type_t<unsigned_list, 4>;
using u64 = find_size_type_t<unsigned_list, 8>;

using f32 = find_size_type_t<floating_point_list, 4>;
using f64 = find_size_type_t<floating_point_list, 8>;

using isize = find_size_type_t<signed_list, sizeof( int* )>;
using usize = find_size_type_t<unsigned_list, sizeof( int* )>;
} // _type_impl

using i8  = _type_impl::i8;
using i16 = _type_impl::i16;
using i32 = _type_impl::i32;
using i64 = _type_impl::i64;

using u8  = _type_impl::u8;
using u16 = _type_impl::u16;
using u32 = _type_impl::u32;
using u64 = _type_impl::u64;

using f32 = _type_impl::f32;
using f64 = _type_impl::f64;

using isize = _type_impl::isize;
using usize = _type_impl::usize;

using byte = u8;

using ipointer     = isize;
using upointer     = usize;
using pointer_diff = isize;
} // namespace pyrite

#endif // PYRITE_CONFIG_TYPE_HPP
