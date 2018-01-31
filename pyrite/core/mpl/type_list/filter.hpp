/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_CORE_MPL_TYPE_LIST_FILTER_HPP
#define PYRITE_CORE_MPL_TYPE_LIST_FILTER_HPP

#include <type_traits>

#include <pyrite/core/mpl/type_list/is_type_list.hpp>
#include <pyrite/core/mpl/type_list/operators.hpp>
#include <pyrite/core/mpl/type_list/type_list.hpp>
#include <pyrite/core/mpl/type_optional.hpp>

namespace pyrite::core::mpl
{
template <typename List, template <typename> typename F>
struct filter
{
  static_assert(is_type_list_v<List>);
};

template <template <typename> typename F, typename... Args>
struct filter<type_list<Args...>, F>
{
private:
  static auto apply()
  {
    return (std::conditional_t<F<Args>::value, type_list<Args>, type_list<>>{} +
            ...);
  }

public:
  using type = decltype(apply());
};

template <typename List, template <typename> typename F>
using filter_t = typename filter<List, F>::type;
} // namespace pyrite::core::mpl

#endif // PYRITE_CORE_MPL_TYPE_LIST_FILTER_HPP
