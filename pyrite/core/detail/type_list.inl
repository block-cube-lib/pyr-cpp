/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */
#ifndef PYRITE_CORE_DETAIL_TYPE_LIST
#define PYRITE_CORE_DETAIL_TYPE_LIST

#include <type_traits>

namespace pyrite
{
namespace core
{
// proto type
template <typename... Args>
struct type_list;

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
// utility
///
template <typename T>
struct type_holder
{
  using type = T;
};

///
// head
///
template <typename>
struct head_
{
  using type = null_type;
};

template <typename Head, typename... Tail>
struct head_<type_list<Head, Tail...>>
{
  using type = Head;
};

///
// tail
///
template <typename>
struct tail_
{
  using type = null_type;
};

template <typename Head, typename... Tail>
struct tail_<type_list<Head, Tail...>>
{
  using type = type_list<Tail...>;
};

///
// at
///
template <typename T, std::size_t>
struct at_
{
  static_assert(mpl::is_type_list_v<T>);
};

template <typename... Args, std::size_t Index>
struct at_<type_list<Args...>, Index>
{
private:
  static auto apply()
  {
    using list = type_list<Args...>;
    if constexpr (Index == 0)
    {
      using head = typename head_<list>::type;
      return type_holder<head>{};
    }
    else
    {
      using tail = typename tail_<list>::type;
      return at_<tail, Index - 1>();
    }
  }

public:
  static_assert(Index < type_list<Args...>::length);
  using type = typename decltype(apply())::type;
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

template <typename List, typename T>
struct push_back_
{
  static_assert(mpl::is_type_list_v<List>);
  using type = typename join_<List, type_list<T>>::type;
};

template <typename List, typename T>
struct push_front_
{
  static_assert(mpl::is_type_list_v<List>);
  using type = typename join_<type_list<T>, List>::type;
};

template <template <typename> typename F, typename... Args>
struct all_of_
{
  static constexpr bool value = (sizeof...(Args) == 0u) ||
                                (F<Args>::value && ...);
};

template <template <typename> typename F, typename... Args>
struct any_of_
{
  static constexpr bool value = (sizeof...(Args) == 0u) ||
                                (F<Args>::value || ...);
};

template <typename T, std::size_t Count>
struct make_type_list_
{
private:
  template <typename... Args>
  static auto apply()
  {
    using add_list        = type_list<Args...>;
    constexpr auto length = sizeof...(Args);

    if constexpr (Count == 0)
    {
      return add_list{};
    }
    else if constexpr (Count == 1)
    {
      using result = typename join_<add_list, type_list<T>>::type;
      return result{};
    }
    else if constexpr (length == 0)
    {
      return apply<T>();
    }
    else if constexpr (length < Count / 2)
    {
      return apply<Args..., Args...>();
    }
    else
    {
      using join_list = typename make_type_list_<T, Count - length>::type;
      using result    = typename join_<add_list, join_list>::type;
      return result{};
    }
  }

public:
  using type = decltype(apply());
};
} // namespace detail

} // namespace core
} // namespace pyrite
#endif // PYRITE_CORE_DETAIL_TYPE_LIST
