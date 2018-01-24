/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MPL_TYPE_LIST_AT_HPP
#define PYRITE_MPL_TYPE_LIST_AT_HPP

#include <type_traits>
#include <utility>

#include <pyrite/mpl/type_list/find_if.hpp>
#include <pyrite/mpl/type_list/is_type_list.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>
#include <pyrite/mpl/type_list/zip.hpp>

namespace pyrite::mpl
{
namespace at_
{
template <typename Sequence>
struct sequence_to_list;

template <std::size_t... Index>
struct sequence_to_list<std::index_sequence<Index...>>
{
  using type = type_list<std::integral_constant<std::size_t, Index>...>;
};

template <typename Sequence>
using sequence_to_list_t = typename sequence_to_list<Sequence>::type;

template <typename Pair, std::size_t Index>
struct is_index_of : std::conditional_t<Pair::second::value == Index,
                                        std::true_type,
                                        std::false_type>
{
};

} // namespace at_

template <typename List, std::size_t Index>
struct at
{
  static_assert(is_type_list_v<List>);
  static_assert(Index < List::size, "out of range");

private:
  using index_sequence  = std::make_index_sequence<List::size>;
  using index_list      = at_::sequence_to_list_t<index_sequence>;
  using type_index_list = zip_t<List, index_list>;

  template <typename Pair>
  using is_index_of = at_::is_index_of<Pair, Index>;

  using founded_pair_optional = find_if_t<type_index_list, is_index_of>;

public:
  using type = typename founded_pair_optional::type::first;
};

template <typename List, std::size_t Index>
using at_t = typename at<List, Index>::type;
} // namespace pyrite::mpl

#endif // PYRITE_MPL_TYPE_LIST_AT_HPP
