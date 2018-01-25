/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_CORE_MPL_TYPE_LIST_IS_TYPE_LIST_HPP
#define PYRITE_CORE_MPL_TYPE_LIST_IS_TYPE_LIST_HPP

#include <type_traits>

#include <pyrite/core/mpl/type_list/type_list.hpp>

namespace pyrite::core::mpl
{
template <typename T>
struct is_type_list : std::false_type
{
};

template <typename... Args>
struct is_type_list<type_list<Args...>> : std::true_type
{
};

template <typename T>
constexpr bool is_type_list_v = is_type_list<T>::value;
} // namespace pyrite::core::mpl

#endif // PYRITE_CORE_MPL_TYPE_LIST_IS_TYPE_LIST_HPP
