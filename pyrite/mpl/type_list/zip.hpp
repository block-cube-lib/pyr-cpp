/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MPL_TYPE_LIST_ZIP_HPP
#define PYRITE_MPL_TYPE_LIST_ZIP_HPP

#include <pyrite/mpl/type_list/is_type_list.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>
#include <pyrite/mpl/type_pair.hpp>

namespace pyrite::mpl
{
template <typename ListL, typename ListR>
struct zip
{
  static_assert(is_type_list_v<ListL>);
  static_assert(is_type_list_v<ListR>);
};

template <typename... L, typename... R>
struct zip<type_list<L...>, type_list<R...>>
{
  static_assert(sizeof...(L) == sizeof...(R));
  using type = type_list<type_pair<L, R>...>;
};

template <typename ListL, typename ListR>
using zip_t = typename zip<ListL, ListR>::type;
} // namespace pyrite::mpl
#endif // PYRITE_MPL_TYPE_LIST_ZIP_HPP
