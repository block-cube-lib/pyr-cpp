#ifndef PYRITE_CORE_TYPE_HOLDER_HPP
#define PYRITE_CORE_TYPE_HOLDER_HPP

namespace pyrite
{
inline namespace core
{
template <typename... T>
struct type_holder
{
  static_assert(sizeof...(T) <= 1);
};

template <typename T>
struct type_holder<T>
{
  using type = T;

  template <typename U>
  using type_or = T;

  static constexpr bool has_type = true;
};

template <>
struct type_holder<>
{
  template <typename U>
  using type_or = U;

  static constexpr bool has_type = false;
};

using null_type_holder = type_holder<>;
} // namespace core
} // namespace pyrite

#endif // PYRITE_CORE_TYPE_HOLDER_HPP
