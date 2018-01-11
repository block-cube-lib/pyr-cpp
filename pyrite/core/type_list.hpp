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
};

template <typename T, std::size_t Count>
struct make_type_list
{
private:
  template <typename AddList = type_list<>>
  static auto apply()
  {
    if constexpr (Count == 0)
    {
      return AddList{};
    }
    else if constexpr (Count == 1)
    {
      using result = typename AddList::template join<type_list<T>>;
      return result{};
    }
    else if constexpr (AddList::length == 0)
    {
      return apply<type_list<T>>();
    }
    else if constexpr (AddList::length < Count / 2)
    {
      using add_list = typename AddList::template join<AddList>;
      return apply<add_list>();
    }
    else
    {
      using list2 = typename make_type_list<T, Count - AddList::length>::type;
      using result = typename AddList::template join<list2>;
      return result{};
    }
  }

public:
  using type = decltype(apply());
};

} // namespace core
} // namespace pyrite

#endif // PYRITE_CORE_TYPE_LIST
