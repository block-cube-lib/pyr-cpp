/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */
#ifndef PYRITE_TYPE_TRAITS_IS_COMPARABLE_HPP
#define PYRITE_TYPE_TRAITS_IS_COMPARABLE_HPP

#include <utility>

#include <pyrite/core/integral_constant.hpp>
#include <pyrite/core/void_t.hpp>

namespace pyrite
{
/**
 * Whether T and U can be compared with operator==.
 * @tparam T Left Type.
 * @tparam U Right Type.
 */
template <typename T, typename U, typename = void>
struct is_equality_comparable : false_type
{
};

/**
 * Template specialization when T and U can be compared with operator==.
 */
template <typename T, typename U>
struct is_equality_comparable<
  T,
  U,
  void_t<decltype(std::declval<T&>() == std::declval<U&>())>> : true_type
{
};

/**
 * Helper variable template of is_equality_comparable.
 */
template <typename T, typename U>
constexpr bool is_equality_comparable_v = is_equality_comparable<T, U>::value;

/**
 * Whether T and nullptr can be compared with operator==.
 */
template <typename T>
using is_null_equality_comparable = is_equality_comparable<T, std::nullptr_t>;

/**
 * Helper variable template of is_null_equality_comparable.
 */
template <typename T>
constexpr bool is_null_equality_comparable_v =
  is_null_equality_comparable<T>::value;
} // namespace pyrite

#endif // PYRITE_TYPE_TRAITS_IS_COMPARABLE_HPP
