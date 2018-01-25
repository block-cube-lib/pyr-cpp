/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MPL_TYPE_LIST_TAIL_HPP
#define PYRITE_MPL_TYPE_LIST_TAIL_HPP

#include <pyrite/mpl/type_list/is_type_list.hpp>
#include <pyrite/mpl/type_list/join.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>

namespace pyrite::mpl
{
template <typename List>
struct tail
{
  static_assert(is_type_list_v<List>);
  using type = type_list<>;
};

template <typename Head, typename... Tail>
struct tail<type_list<Head, Tail...>>
{
  using type = type_list<Tail...>;
};

template <typename List>
using tail_t = typename tail<List>::type;
} // namespace pyrite::mpl
#endif // PYRITE_MPL_TYPE_LIST_TAIL_HPP
