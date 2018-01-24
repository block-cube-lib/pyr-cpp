/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_CORE_MPL_TYPE_LIST_HEAD_HPP
#define PYRITE_CORE_MPL_TYPE_LIST_HEAD_HPP

#include <pyrite/core/mpl/type_list/is_type_list.hpp>
#include <pyrite/core/mpl/type_list/type_list.hpp>
#include <pyrite/core/mpl/type_optional.hpp>

namespace pyrite::core::mpl
{
template <typename T>
struct head
{
  static_assert(is_type_list_v<T>);
  using type = null_type_optional;
};

template <typename Head, typename... Tail>
struct head<type_list<Head, Tail...>>
{
  using type = type_optional<Head>;
};

template <typename List>
using head_t = typename head<List>::type;
} // namespace pyrite::core::mpl

#endif // PYRITE_CORE_MPL_TYPE_LIST_HEAD_HPP
