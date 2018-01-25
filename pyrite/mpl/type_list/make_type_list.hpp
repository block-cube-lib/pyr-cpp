/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MPL_TYPE_LIST_MAKE_TYPE_LIST_HPP
#define PYRITE_MPL_TYPE_LIST_MAKE_TYPE_LIST_HPP

#include <cstddef> // std::size_t
#include <utility> // index_sequence

#include <pyrite/mpl/type_list/is_type_list.hpp>
#include <pyrite/mpl/type_list/operators.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>

namespace pyrite::mpl
{
namespace make_type_list_
{
template <typename T, std::size_t Size>
struct make_type_list
{
private:
  template <std::size_t Index>
  using index_to_type = T;

  template <std::size_t... Index>
  static auto apply(std::index_sequence<Index...>)
    -> decltype((type_list<index_to_type<Index>>{} + ...));

  using sequence = std::make_index_sequence<Size>;

public:
  using type = decltype(apply(sequence{}));
};

template <typename T>
struct make_type_list<T, 0>
{
  using type = type_list<>;
};
} // namespace make_type_list_

template <typename List, std::size_t Size>
using make_type_list =
  typename make_type_list_::make_type_list<List, Size>::type;
} // namespace pyrite::mpl

#endif // PYRITE_MPL_TYPE_LIST_MAKE_TYPE_LIST_HPP
