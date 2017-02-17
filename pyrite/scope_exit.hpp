/**
 * @file
 * @brief     Define scope_exit
 *
 * @date      2017/02/16 Create
 *
 * @author    block
 *
 * @copyright 2016 block (c)copyright all rights reserved.
 */

#ifndef PYRITE_SCOPE_EXIT
#define PYRITE_SCOPE_EXIT

namespace pyrite
{
namespace _scope_exit_impl
{
template <typename T>
struct is_null_comparable
{
private:
  template <typename U>
  static constexpr auto check( U* u ) -> decltype( *u == nullptr, bool{} )
  {
    return true;
  }

  template <typename U>
  static constexpr auto check( ... ) -> bool
  {
    return false;
  }

public:
  static constexpr bool value = check<T>( nullptr );
};

template <typename F, bool IsNullComparable = is_null_comparable<F>::value>
struct call;

template <typename F>
struct call<F, true>
{
  static void apply( F& function )
  {
    if( function != nullptr )
    {
      function();
    }
  }
};

template <typename F>
struct call<F, false>
{
  static void apply( F& function ) { function(); }
};

} // namespace _scope_exit_impl

template <typename F>
class scope_exit
{
public:
  scope_exit( F const& function ) : function_( function ) {}
  scope_exit( scope_exit && ) = default;

  ~scope_exit() { _scope_exit_impl::call<F>::apply( function_ ); }

  scope_exit& operator=(scope_exit&& rhs) = default;

  //
  // delete functions
  //
  scope_exit()                    = delete;
  scope_exit( scope_exit const& ) = delete;
  scope_exit& operator=( scope_exit& ) = delete;

private:
  F function_;
}; // class scope_exit

template <typename F>
scope_exit<F> make_scope_exit( F const& function )
{
  return {function};
}
} // namespace pyrite

#endif // PYRITE_SCOPE_EXIT
