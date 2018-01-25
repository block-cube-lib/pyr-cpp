/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_CORE_MPL_TYPE_OPTIONAL_HPP
#define PYRITE_CORE_MPL_TYPE_OPTIONAL_HPP

namespace pyrite::core::mpl
{
template <typename... T>
struct type_optional
{
  static_assert(sizeof...(T) <= 1);
};

template <typename T>
struct type_optional<T>
{
  using type = T;

  template <typename U>
  using type_or = T;

  static constexpr bool has_type = true;
};

template <>
struct type_optional<>
{
  template <typename U>
  using type_or = U;

  static constexpr bool has_type = false;
};

using null_type_optional = type_optional<>;
} // namespace pyrite

#endif // PYRITE_CORE_MPL_TYPE_OPTIONAL_HPP
