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

  static constexpr decltype(sizeof...(Args)) length = sizeof...(Args);

  using head = typename detail::head_<type>::type;
  using tail = typename detail::tail_<type>::type;

  template <typename T>
  using join = typename detail::join_<type, T>::type;
};
} // namespace core
} // namespace pyrite

#endif // PYRITE_CORE_TYPE_LIST
