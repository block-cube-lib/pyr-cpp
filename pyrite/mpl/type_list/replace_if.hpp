/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MPL_TYPE_LIST_REPLACE_IF_HPP
#define PYRITE_MPL_TYPE_LIST_REPLACE_IF_HPP

#include <type_traits>

#include <pyrite/mpl/type_list/is_type_list.hpp>
#include <pyrite/mpl/type_list/transform.hpp>
#include <pyrite/mpl/type_list/type_list.hpp>

namespace pyrite::mpl
{
template <typename List, template <typename> typename Pred, typename NewType>
struct replace_if
{
private:
  template <typename T>
  struct replace_pred
  {
    using type = std::conditional_t<Pred<T>::value, NewType, T>;
  };

public:
  using type = transform_t<List, replace_pred>;
};

template <typename List, template <typename> typename Pred, typename NewType>
using replace_if_t = typename replace_if<List, Pred, NewType>::type;
} // namespace pyrite::mpl

#endif // PYRITE_MPL_TYPE_LIST_REPLACE_IF_HPP
