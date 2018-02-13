#ifndef PYRITE_GRAPHICS_COLOR_HPP
#define PYRITE_GRAPHICS_COLOR_HPP

#include <limits>
#include <type_traits>

#include <pyrite/math/utility.hpp>
#include <pyrite/math/vector.hpp>

namespace pyrite::graphics
{
template <typename T>
class color
{
public:
  /****************************************************************************
   * type alias
   ****************************************************************************/
  using value_type = T;
  using vector_value_type =
    std::conditional_t<std::is_floating_point_v<T>, T, double>;

  /****************************************************************************
   * constructor
   ****************************************************************************/
  constexpr color() noexcept = default;
  constexpr color(T r, T g, T b, T a = max_value) noexcept;
  constexpr color(color const& other) noexcept = default;
  constexpr color(u32 rrggbbaa) noexcept;

  template <typename U>
  constexpr color(color<U> const& other);

  template <typename U = vector_value_type>
  constexpr color(pyrite::math::vector<U, 4> const& v);

  /****************************************************************************
   * member function
   ****************************************************************************/
  template <typename U>
  constexpr color<U> convert() const;

  /****************************************************************************
   * operator
   ****************************************************************************/
  color& operator=(color const& other) noexcept;
  color& operator=(color&& other) noexcept;

  template <typename U = vector_value_type>
  explicit constexpr operator pyrite::math::vector<U, 4>() const;

  /****************************************************************************
   * member variable
   ****************************************************************************/
  T r{0};         //!< red
  T g{0};         //!< green
  T b{0};         //!< blue
  T a{max_value}; //!< alpha

private:
  /****************************************************************************
   * private static member variable
   ****************************************************************************/
  static constexpr T max_value =
    std::is_integral_v<T> ? std::numeric_limits<T>::max() : T{1};
};
} // namespace pyrite::graphics

#  include <pyrite/graphics/color/implementation.hpp>

#endif // PYRITE_GRAPHICS_COLOR_HPP
