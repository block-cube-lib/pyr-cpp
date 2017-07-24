/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */
#ifndef PYRITE_TYPE_TRAITS_IS_EQUALITY_COMPARABLE_HPP
#define PYRITE_TYPE_TRAITS_IS_EQUALITY_COMPARABLE_HPP

#include <pyrite/core/void_t.hpp>

namespace pyrite
{
template <typename T, typename U, typename = void>
struct is_equality_comparable : false_type
{
};

template <typename T, typename U>
struct is_equality_comparable<
  T,
  U,
  void_t<decltype( std::declval<T&>() == std::declval<U&>() )>> : true_type
{
};

template <typename T, typename U>
constexpr bool is_equality_comparable_v = is_equality_comparable<T, U>::value;

template <typename T>
using is_null_equality_comparable = is_equality_comparable<T, std::nullptr_t>;

template <typename T>
constexpr bool is_null_equality_comparable_v = is_null_equality_comparable<T>::value;
}

#endif // PYRITE_TYPE_TRAITS_IS_COMPARABLE_HPP
