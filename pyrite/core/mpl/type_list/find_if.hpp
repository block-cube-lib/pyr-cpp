/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_CORE_MPL_TYPE_LIST_FIND_IF_HPP
#define PYRITE_CORE_MPL_TYPE_LIST_FIND_IF_HPP

#include <pyrite/core/mpl/type_list/filter.hpp>
#include <pyrite/core/mpl/type_list/head.hpp>
#include <pyrite/core/mpl/type_list/is_type_list.hpp>
#include <pyrite/core/mpl/type_optional.hpp>

namespace pyrite::core::mpl
{
template <typename List, template <typename> typename F>
struct find_if
{
public:
  using type = head_t<filter_t<List, F>>;
};

template <typename List, template <typename> typename F>
using find_if_t = typename find_if<List, F>::type;
} // namespace pyrite::core::mpl

#endif // PYRITE_CORE_MPL_TYPE_LIST_FIND_IF_HPP
