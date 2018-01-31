/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */
#ifndef PYRITE_MPL_TYPE_LIST_NONE_OF_HPP
#define PYRITE_MPL_TYPE_LIST_NONE_OF_HPP

#include <type_traits>

#include <pyrite/mpl/type_list/is_type_list.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>

namespace pyrite::mpl
{

namespace detail
{
namespace
{
template <typename List, template <typename> typename F>
struct none_of
{
  static_assert(is_type_list_v<List>);
};

template <typename... T, template <typename> typename F>
struct none_of<type_list<T...>, F>
{
  static constexpr bool apply()
  {
    return sizeof...(T) == 0 || (!F<T>::value && ...);
  }
};
} // namespace
} // namespace detail

template <typename List, template <typename> typename F>
struct none_of : std::bool_constant<detail::none_of<List, F>::apply()>
{
};

template <typename List, template <typename> typename F>
constexpr bool none_of_v = none_of<List, F>::value;

} // namespace pyrite::mpl

#endif // PYRITE_MPL_TYPE_LIST_NONE_OF_HPP
