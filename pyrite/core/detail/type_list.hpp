/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */
#ifndef PYRITE_CORE_DETAIL_TYPE_LIST_HPP
#define PYRITE_CORE_DETAIL_TYPE_LIST_HPP

#include <type_traits>

#include <pyrite/core/type_holder.hpp>

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
      using head_holder = typename head_<list>::type;
      return type_holder<typename head_holder::type>{};
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
template <template <typename> typename F, typename... Args>
struct transform_
{
  using type = type_list<typename F<Args>::type...>;
};

///
// find_if
///
template <typename List, template <typename> typename F>
struct find_if_
{
private:
  template <typename L>
  static auto find()
  {
    using head_holder = typename head_<L>::type;
    if constexpr (head_holder::has_type)
    {
      using head = typename head_holder::type;
      if constexpr (F<head>::value)
      {
        return type_holder<head>{};
      }
      else
      {
        return find<typename tail_<L>::type>();
      }
    }
    else
    {
      return type_holder<>{};
    }
  }

public:
  using type = decltype(find<List>());
};

///
// make_type_list
///
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
#endif // PYRITE_CORE_DETAIL_TYPE_LIST_HPP
