/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MPL_TYPE_LIST_PUSH_FRONT_HPP
#define PYRITE_MPL_TYPE_LIST_PUSH_FRONT_HPP

#include <pyrite/mpl/type_list/is_type_list.hpp>
#include <pyrite/mpl/type_list/join.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>

namespace pyrite::mpl
{
template <typename List, typename T>
struct push_front
{
  static_assert(is_type_list_v<List>);
  using type = join_t<type_list<T>, List>;
};

template <typename List, typename T>
using push_front_t = typename push_front<List, T>::type;
} // namespace pyrite::mpl
#endif // PYRITE_MPL_TYPE_LIST_PUSH_FRONT_HPP
