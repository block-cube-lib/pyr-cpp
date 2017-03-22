/**
 * @file
 * @author    block
 * @copyrite  (c)
 */

#ifndef PYRITE_CORE_IS_COMPLETE_TYPE_HPP
#define PYRITE_CORE_IS_COMPLETE_TYPE_HPP

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
 *
 * @tparam T A a type to check.
 */
template <typename T>
class is_complete_type : public _impl::is_complete_type<T>::type
{
};
} // namespace pyrite

#endif // PYRITE_CORE_IS_COMPLETE_TYPE_HPP
