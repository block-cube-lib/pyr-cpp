/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MPL_TYPE_LIST_PUSH_BACK_HPP
#define PYRITE_MPL_TYPE_LIST_PUSH_BACK_HPP

#include <pyrite/mpl/type_list/is_type_list.hpp>
#include <pyrite/mpl/type_list/join.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>

namespace pyrite::mpl
{
template <typename List, typename T>
struct push_back
{
  static_assert(is_type_list_v<List>);
  using type = join_t<List, type_list<T>>;
};

template <typename List, typename T>
using push_back_t = typename push_back<List, T>::type;
} // namespace pyrite::mpl
#endif // PYRITE_MPL_TYPE_LIST_PUSH_BACK_HPP
