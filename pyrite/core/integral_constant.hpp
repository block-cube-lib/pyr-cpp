/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_INTEGRAL_CONSTANT_HPP
#define PYRITE_INTEGRAL_CONSTANT_HPP

namespace pyrite
{
/**
 * integral_constant wraps a static constant of specified type.
 * @tparam T Integer type.
 * @tparam V A T type value.
 */
template <typename T, T V>
struct integral_constant
{
  using value_type = T;                 //!< Alias of type T.
  using type = integral_constant<T, V>; //!< Alias of integral_constant<T, V>.

  static constexpr T value{V}; //!< static constant of type T with value v.

  /**
   * Concersion function.
   * Returns the wrapped value.
   * @return Value
   */
  constexpr operator value_type() const noexcept { return value; }

  /**
   * Returns the wrapped value.
   * This function enables integral_constant to serve as a source of compile-time function objects.
   * @return Value
   */
  constexpr value_type operator()() const noexcept { return value; }
};

/**
 * Alias of integral_constant<bool, V>
 * @tparam B A bool type value.
 */
template <bool B>
using bool_constant = integral_constant<bool, B>;

using true_type  = bool_constant<true>;  //!< An alias whose value is true.
using false_type = bool_constant<false>; //!< An alias whose value is false.

} // namespace pyrite

#endif // PYRITE_INTEGRAL_CONSTANT_HPP
