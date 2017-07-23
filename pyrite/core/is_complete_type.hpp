/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_CORE_IS_COMPLETE_TYPE_HPP
#define PYRITE_CORE_IS_COMPLETE_TYPE_HPP

#include <pyrite/core/integral_constant.hpp>

namespace pyrite
{
namespace _impl
{
template <typename T>
class is_complete_type
{
private:
  template <typename U>
  static auto check( U* ) -> decltype( sizeof( U ), pyrite::true_type{} );
  template <typename U>
  static auto check( ... ) -> decltype( pyrite::false_type{} );

public:
  using type = decltype( check<T>( nullptr ) );
};
} // namespace _impl

/**
 * Checks whether T is an complete type.
 * @tparam T A a type to check.
 */
template <typename T>
class is_complete_type : public _impl::is_complete_type<T>::type
{
};

/**
 * Variable template version of is_complete_type.
 */
template <typename T>
constexpr bool is_complete_type_v = is_complete_type<T>::value;

} // namespace pyrite

#endif // PYRITE_CORE_IS_COMPLETE_TYPE_HPP
