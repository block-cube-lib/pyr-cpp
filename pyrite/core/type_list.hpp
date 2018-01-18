/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_CORE_TYPE_LIST_HPP
#define PYRITE_CORE_TYPE_LIST_HPP

#include <pyrite/core/detail/type_list.hpp>

namespace pyrite
{
namespace core
{
template <typename... Args>
struct type_list
{
public:
  using type = type_list<Args...>;

  static constexpr std::size_t length = sizeof...(Args);

  using head = typename detail::head_<type>::type;
  using tail = typename detail::tail_<type>::type;

  template <std::size_t Index>
  using at = typename detail::at_<type, Index>::type;

  template <typename T>
  using join = typename detail::join_<type, T>::type;

  template <typename T>
  using push_back = typename detail::push_back_<type, T>::type;

  template <typename T>
  using push_front = typename detail::push_front_<type, T>::type;

  template <template <typename> typename Pred>
  static constexpr bool all_of = detail::all_of_<Pred, Args...>::value;

  template <template <typename> typename Pred>
  static constexpr bool any_of = detail::any_of_<Pred, Args...>::value;

  template <template <typename> typename Pred>
  static constexpr bool none_of = detail::none_of_<Pred, Args...>::value;

  template <template <typename> typename Pred>
  using transform = typename detail::transform_<Pred, Args...>::type;

  template <template <typename> typename Pred>
  using find_if = typename detail::find_if_<type, Pred>::type;
}; // namespace coretemplate<typename...Args>structtype_list

template <typename T, std::size_t Size>
using make_type_list = typename detail::make_type_list_<T, Size>::type;
} // namespace core
} // namespace pyrite

#endif // PYRITE_CORE_TYPE_LIST_HPP
