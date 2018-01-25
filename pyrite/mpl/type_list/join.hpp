/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MPL_TYPE_LIST_JOIN_HPP
#define PYRITE_MPL_TYPE_LIST_JOIN_HPP

#include <pyrite/mpl/type_list/is_type_list.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>

namespace pyrite::mpl
{
template <typename ListL, typename ListR>
struct join
{
  static_assert(is_type_list_v<ListL>);
  static_assert(is_type_list_v<ListR>);
};
template <typename... L, typename... R>
struct join<type_list<L...>, type_list<R...>>
{
  using type = type_list<L..., R...>;
};

template <typename ListL, typename ListR>
using join_t = typename join<ListL, ListR>::type;
} // namespace pyrite::mpl

#endif // PYRITE_MPL_TYPE_LIST_JOIN_HPP
