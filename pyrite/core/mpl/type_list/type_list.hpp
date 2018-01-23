/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */
#ifndef PYRITE_CORE_MPL_TYPE_LIST_TYPE_LIST_HPP
#define PYRITE_CORE_MPL_TYPE_LIST_TYPE_LIST_HPP

#include <type_traits>
#include <utility>

#include <pyrite/core/mpl/type_holder.hpp>

namespace pyrite
{
namespace core
{
// proto type
template <typename... Args>
struct type_list;

template <typename... T, typename... U>
auto operator+(type_list<T...> const&, type_list<U...> const&)
  -> type_list<T..., U...>;

namespace mpl
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
} // namespace mpl

namespace detail
{
///
// size
///
template <typename List>
struct list_size
{
  static_assert(mpl::is_type_list_v<List>);
};

template <typename... Args>
struct list_size<type_list<Args...>>
{
  static constexpr std::size_t value = sizeof...(Args);
};

template <typename List>
static constexpr std::size_t list_size_v = list_size<List>::value;

///
// utility
///
template <typename T, std::size_t Index>
struct with_index
{
  using type                         = T;
  static constexpr std::size_t index = Index;
};

template <typename List, typename Sequence>
struct list_to_with_index_list;

template <typename... Types, std::size_t... Indices>
struct list_to_with_index_list<type_list<Types...>,
                               std::index_sequence<Indices...>>
{
  using type = type_list<with_index<Types, Indices>...>;
};

template <typename List>
using list_sequence = std::make_index_sequence<list_size_v<List>>;

template <typename List>
using to_with_index_list =
  typename list_to_with_index_list<List, list_sequence<List>>::type;

///
// head
///
template <typename T>
struct head_
{
  static_assert(mpl::is_type_list_v<T>);
  using type = null_type_holder;
};

template <typename Head, typename... Tail>
struct head_<type_list<Head, Tail...>>
{
  using type = type_holder<Head>;
};

///
// tail
///
template <typename>
struct tail_
{
  using type = type_list<>;
};

template <typename Head, typename... Tail>
struct tail_<type_list<Head, Tail...>>
{
  using type = type_list<Tail...>;
};

///
// at
///
template <typename List, std::size_t Index>
struct with_index_list_at;

template <typename... WithIndex, std::size_t Index>
struct with_index_list_at<type_list<WithIndex...>, Index>
{
private:
  template <typename T, std::size_t I>
  static auto type_to_list()
    -> std::conditional_t<I == Index, type_list<T>, type_list<>>;

  using list = decltype(
    (type_to_list<typename WithIndex::type, WithIndex::index>() + ...));
  using head_holder = typename list::head;

public:
  using type = typename head_holder::type;
};

template <typename List, std::size_t Index>
struct at_
{
  static_assert(mpl::is_type_list_v<List>);
  static_assert(0 < list_size_v<List> && Index < list_size_v<List>,
                "out of range");

private:
  using with_index_list = to_with_index_list<List>;

public:
  using type = typename with_index_list_at<with_index_list, Index>::type;
};

///
// join
///
template <typename L, typename R>
struct join_
{
  static_assert(mpl::is_type_list_v<L>);
  static_assert(mpl::is_type_list_v<R>);
};

template <typename... L, typename... R>
struct join_<type_list<L...>, type_list<R...>>
{
  using type = type_list<L..., R...>;
};

///
// push_back
///
template <typename List, typename T>
struct push_back_
{
  static_assert(mpl::is_type_list_v<List>);
  using type = typename join_<List, type_list<T>>::type;
};

///
// push_front
///
template <typename List, typename T>
struct push_front_
{
  static_assert(mpl::is_type_list_v<List>);
  using type = typename join_<type_list<T>, List>::type;
};

///
// all_of
///
template <template <typename> typename F, typename... Args>
struct all_of_
{
  static constexpr bool value = (sizeof...(Args) == 0u) ||
                                (F<Args>::value && ...);
};

///
// any_of
///
template <template <typename> typename F, typename... Args>
struct any_of_
{
  static constexpr bool value = (sizeof...(Args) == 0u) ||
                                (F<Args>::value || ...);
};

///
// none_of
///
template <template <typename> typename F, typename... Args>
struct none_of_
{
  static constexpr bool value = (sizeof...(Args) == 0u) ||
                                (!F<Args>::value && ...);
};

///
// transform
///
template <template <typename> typename F, typename List>
struct transform_;

template <template <typename> typename F>
struct transform_<F, type_list<>>
{
  using type = type_list<>;
};

template <template <typename> typename F, typename... Args>
struct transform_<F, type_list<Args...>>
{
  using type = type_list<typename F<Args>::type...>;
};

///
// filter
///
template <typename List, template <typename> typename F>
struct filter_
{
  static_assert(mpl::is_type_list_v<List>);
};

template <template <typename> typename F, typename... Args>
struct filter_<type_list<Args...>, F>
{
  using type = decltype(
    (std::conditional_t<F<Args>::value, type_list<Args>, type_list<>>{} + ...));
};

///
// find_if
///
template <typename List, template <typename> typename F>
struct find_if_
{
private:
  using filtered = typename filter_<List, F>::type;

public:
  using type = typename head_<filtered>::type;
};

///
// reverse
///
template <typename List>
struct reverse_
{
private:
  static constexpr std::size_t last_index = list_size_v<List> - 1;
  using with_index_list                   = to_with_index_list<List>;

  template <typename WithIndex>
  struct apply
  {
    using type = typename at_<List, last_index - WithIndex::index>::type;
  };

  using transformed = typename transform_<apply, with_index_list>::type;

public:
  using type = transformed;
};

template <>
struct reverse_<type_list<>>
{
  using type = type_list<>;
};

///
// make_type_list
///
template <typename T, std::size_t Count>
struct make_type_list_
{
private:
  template <std::size_t I>
  using index_to_type = T;

  template <std::size_t... Index>
  static auto apply(std::index_sequence<Index...>)
    -> decltype((type_list<index_to_type<Index>>{} + ...));

  using sequence = std::make_index_sequence<Count>;

public:
  using type = decltype(apply(sequence{}));
};
template <typename T>
struct make_type_list_<T, 0>
{
  using type = type_list<>;
};
} // namespace detail

} // namespace core
} // namespace pyrite
#endif // PYRITE_CORE_MPL_TYPE_LIST_TYPE_LIST_HPP
