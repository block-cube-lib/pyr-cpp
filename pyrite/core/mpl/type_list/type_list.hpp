/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */
#ifndef PYRITE_CORE_MPL_TYPE_LIST_TYPE_LIST_HPP
#define PYRITE_CORE_MPL_TYPE_LIST_TYPE_LIST_HPP

#include <cstddef> // std::size_t

namespace pyrite::core::mpl
{
template <typename... Args>
struct type_list
{
  using type = type_list<Args...>;

  static constexpr std::size_t size = sizeof...(Args);
};
} // namespace pyrite::core::mpl
#endif // PYRITE_CORE_MPL_TYPE_LIST_TYPE_LIST_HPP
