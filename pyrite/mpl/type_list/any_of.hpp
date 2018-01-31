/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */
#ifndef PYRITE_MPL_TYPE_LIST_ANY_OF_HPP
#define PYRITE_MPL_TYPE_LIST_ANY_OF_HPP

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
struct any_of_base
{
  static_assert(is_type_list_v<List>);
};

template <typename... T, template <typename> typename F>
struct any_of_base<type_list<T...>, F>
{
private:
  static constexpr bool apply()
  {
    return sizeof...(T) == 0 || (F<T>::value || ...);
  }

public:
  using type = std::bool_constant<apply()>;
};
} // namespace
} // namespace detail

template <typename List, template <typename> typename F>
struct any_of : detail::any_of_base<List, F>::type
{
};

template <typename List, template <typename> typename F>
constexpr bool any_of_v = any_of<List, F>::value;

} // namespace pyrite::mpl

#endif // PYRITE_MPL_TYPE_LIST_ANY_OF_HPP
