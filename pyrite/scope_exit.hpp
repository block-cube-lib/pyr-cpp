/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_SCOPE_EXIT_HPP
#define PYRITE_SCOPE_EXIT_HPP

#include <type_traits>

#include <pyrite/core/noncopyable.hpp>
#include <pyrite/type_traits/is_equality_comparable.hpp>

namespace pyrite
{
/**
 * Call the function when you exit the scope.
 * @tparam F The type of function to call.
 */
template <typename F>
class scope_exit : private noncopyable
{
public:
  /**
   * Constructor.
   *
   * @param[in] function Function to be called when exiting the scope.
   */
  scope_exit(F const& function) : function_(function) {}

  /**
   * Move constructor.
   */
  scope_exit(scope_exit&&) = default;

  /**
   * Destructor.
   * Call the function received in the constructor.
   */
  ~scope_exit()
  {
    if constexpr (type_traits::is_equality_comparable_v<F, std::nullptr_t>)
    {
      if (function_ == nullptr)
      {
        return;
      }
    }

    function_();
  }

  /**
   * Move assignment operator.
   */
  scope_exit& operator=(scope_exit&&) = default;

private:
  F function_;
}; // class scope_exit

/**
 * Create scope_exit with the received function as an argument.
 * @param[in] function Function to be called when exiting the scope.
 * @return scope_exit witch calls the argument function.
 */
template <typename F>
scope_exit<F> make_scope_exit(F const& function)
{
  return {function};
}
} // namespace pyrite

#endif // PYRITE_SCOPE_EXIT_HPP
