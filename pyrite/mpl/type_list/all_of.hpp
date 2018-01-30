/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */
#ifndef PYRITE_MPL_TYPE_LIST_ALL_OF_HPP
#define PYRITE_MPL_TYPE_LIST_ALL_OF_HPP

#include <type_traits>

#include <pyrite/mpl/type_list/is_type_list.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>

namespace pyrite::mpl
{
template <typename List, template <typename> typename F>
struct all_of
{
  static_assert(is_type_list_v<List>);
};

template <typename... T, template <typename> typename F>
struct all_of<type_list<T...>, F>
  : std::bool_constant<sizeof...(T) == 0 || (F<T>::value && ...)>
{
};

template <typename List, template <typename> typename F>
constexpr bool all_of_v = all_of<List, F>::value;

} // namespace pyrite::mpl

#endif // PYRITE_MPL_TYPE_LIST_ALL_OF_HPP