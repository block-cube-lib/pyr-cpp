/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_CORE_TYPE_LIST
#define PYRITE_CORE_TYPE_LIST

#include <type_traits>

namespace pyrite
{
struct null_type;
}

namespace pyrite
{
namespace core
{
template <typename... Args>
struct type_list
{
private:
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

public:
  using type = type_list<Args...>;
  using head = typename head_<type>::type;
  using tail = typename tail_<type>::type;

  static constexpr decltype(sizeof...(Args)) length = sizeof...(Args);
};
} // namespace core
} // namespace pyrite

#endif // PYRITE_CORE_TYPE_LIST
