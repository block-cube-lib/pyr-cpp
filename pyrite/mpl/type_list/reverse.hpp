/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MPL_TYPE_LIST_REVERSE_HPP
#define PYRITE_MPL_TYPE_LIST_REVERSE_HPP

#include <cstddef> // std::size_t
#include <utility> // index_sequence

#include <pyrite/mpl/type_list/at.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>

namespace pyrite::mpl
{
namespace reverse_
{
template <typename Sequence>
struct sequence_reverse;

template <std::size_t... Index>
struct sequence_reverse<std::index_sequence<Index...>>
{
  using type = std::index_sequence<(sizeof...(Index) - 1 - Index)...>;
};

template <typename Sequence>
using reversed_sequence = typename sequence_reverse<Sequence>::type;

template <typename List, typename Sequence>
struct sequence_to_list_;
template <typename List, std::size_t... Index>
struct sequence_to_list_<List, std::index_sequence<Index...>>
{
  using type = type_list<at_t<List, Index>...>;
};

template <typename List, typename Sequence>
using sequence_to_list = typename sequence_to_list_<List, Sequence>::type;
} // namespace reverse_

template <typename List>
struct reverse
{
  static_assert(is_type_list_v<List>);

private:
  using sequence          = std::make_index_sequence<List::size>;
  using reversed_sequence = reverse_::reversed_sequence<sequence>;

public:
  using type = reverse_::sequence_to_list<List, reversed_sequence>;
};

template <>
struct reverse<type_list<>>
{
  using type = type_list<>;
};

template <typename List>
using reverse_t = typename reverse<List>::type;
} // namespace pyrite::mpl

#endif // PYRITE_MPL_TYPE_LIST_REVERSE_HPP
