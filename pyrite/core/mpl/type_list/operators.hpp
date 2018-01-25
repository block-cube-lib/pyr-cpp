/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_CORE_MPL_TYPE_LIST_OPERATORS_HPP
#define PYRITE_CORE_MPL_TYPE_LIST_OPERATORS_HPP

#include <pyrite/core/mpl/type_list/type_list.hpp>

namespace pyrite::core::mpl
{
template <typename... T, typename... U>
constexpr auto
  operator+(type_list<T...> const&, type_list<U...> const&) noexcept
{
  return type_list<T..., U...>{};
}
} // namespace pyrite::core::mpl

#endif // PYRITE_CORE_MPL_TYPE_LIST_OPERATORS_HPP
