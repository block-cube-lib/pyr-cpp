/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */
#ifndef PYRITE_TYPE_TRAITS_IS_EQUALITY_COMPARABLE_HPP
#define PYRITE_TYPE_TRAITS_IS_EQUALITY_COMPARABLE_HPP

#include <type_traits>
#include <utility>

namespace pyrite
{
namespace type_traits
{
/**
 * Whether T and U can be compared with operator==.
 * @tparam T Left Type.
 * @tparam U Right Type.
 */
template <typename T, typename U, typename = void>
struct is_equality_comparable : std::false_type
{
};

/**
 * Template specialization when T and U can be compared with operator==.
 */
template <typename T, typename U>
struct is_equality_comparable<
  T,
  U,
  std::void_t<decltype(std::declval<T&>() == std::declval<U&>())>> : std::true_type
{
};

/**
 * Helper variable template of is_equality_comparable.
 */
template <typename T, typename U>
constexpr bool is_equality_comparable_v = is_equality_comparable<T, U>::value;
} // namespace type_traits
} // namespace pyrite

#endif // PYRITE_TYPE_TRAITS_IS_EQUALITY_COMPARABLE_HPP
