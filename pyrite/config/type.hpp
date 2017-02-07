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

template <typename T>
struct type_holder
{
  using type = T;
};

template <typename List, unsigned long long Size>
auto find_size_type()
{
  static_assert( !is_empty_list<List>::value, "not found." );

  using head = typename List::head;

  if
    constexpr( sizeof( head ) == Size ) { return type_holder<head>{}; }
  else
  {
    return find_size_type<typename List::tail, Size>();
  }
}

template <typename List, unsigned long long Size>
using find_size_type_t =
  typename decltype( find_size_type<List, Size>() )::type;

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

using s8  = find_size_type_t<signed_list, 1>;
using s16 = find_size_type_t<signed_list, 2>;
using s32 = find_size_type_t<signed_list, 4>;
using s64 = find_size_type_t<signed_list, 8>;

using u8  = find_size_type_t<unsigned_list, 1>;
using u16 = find_size_type_t<unsigned_list, 2>;
using u32 = find_size_type_t<unsigned_list, 4>;
using u64 = find_size_type_t<unsigned_list, 8>;

using f32 = find_size_type_t<floating_point_list, 4>;
using f64 = find_size_type_t<floating_point_list, 8>;

using isize = find_size_type_t<signed_list, sizeof( int* )>;
using usize = find_size_type_t<unsigned_list, sizeof( int* )>;
} // _type_impl

using s8  = _type_impl::s8;
using s16 = _type_impl::s16;
using s32 = _type_impl::s32;
using s64 = _type_impl::s64;

using u8  = _type_impl::u8;
using u16 = _type_impl::u16;
using u32 = _type_impl::u32;
using u64 = _type_impl::u64;

using f32 = _type_impl::f32;
using f64 = _type_impl::f64;

} // namespace pyrite

#endif // PYRITE_CONFIG_TYPE_HPP
