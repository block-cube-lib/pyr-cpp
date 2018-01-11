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
template <typename T>
struct type_holder
{
  using type = T;
};

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

} // namespace detail

} // namespace core
} // namespace pyrite
#endif // PYRITE_CORE_DETAIL_TYPE_LIST
