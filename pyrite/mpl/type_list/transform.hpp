/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */
#ifndef PYRITE_MPL_TYPE_LIST_TRANSFORM_HPP
#define PYRITE_MPL_TYPE_LIST_TRANSFORM_HPP

#include <pyrite/mpl/type_list/type_list.hpp>

namespace pyrite::mpl
{
template <typename List, template <typename> typename F>
struct transform
{
  static_assert(is_type_list_v<List>);
};

template <typename... T, template <typename> typename F>
struct transform<type_list<T...>, F>
{
  using type = type_list<typename F<T>::type...>;
};

template <typename List, template <typename> typename F>
using transform_t = typename transform<List, F>::type;
} // namespace pyrite::mpl

#endif // PYRITE_MPL_TYPE_LIST_TRANSFORM_HPP
