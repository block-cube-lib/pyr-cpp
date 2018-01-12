/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_CORE_TYPE_LIST
#define PYRITE_CORE_TYPE_LIST

namespace pyrite
{
struct null_type;
}

#include <pyrite/core/detail/type_list.inl>

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
};

template <typename T, std::size_t Size>
using make_type_list = typename detail::make_type_list_<T, Size>::type;

} // namespace core
} // namespace pyrite

#endif // PYRITE_CORE_TYPE_LIST
