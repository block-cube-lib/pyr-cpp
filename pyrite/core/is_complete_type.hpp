/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_CORE_IS_COMPLETE_TYPE_HPP
#define PYRITE_CORE_IS_COMPLETE_TYPE_HPP

#include <pyrite/core/integral_constant.hpp>
#include <pyrite/core/void_t.hpp>

namespace pyrite
{
/**
 * Checks whether T is an complete type.
 * @tparam T A type to check.
 */
template <typename T, typename = void>
class is_complete_type : public false_type
{
};

/**
 * Template specialization when T is complete type.
 */
template <typename T>
class is_complete_type<T, void_t<decltype(sizeof(T))>> : public true_type
{
};

/**
 * Variable template version of is_complete_type.
 */
template <typename T>
constexpr bool is_complete_type_v = is_complete_type<T>::value;

} // namespace pyrite

#endif // PYRITE_CORE_IS_COMPLETE_TYPE_HPP
