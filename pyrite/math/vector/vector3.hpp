/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_VECTOR_VECTOR3_HPP
#define PYRITE_MATH_VECTOR_VECTOR3_HPP

#include <initializer_list>
#include <type_traits>

#include <pyrite/core/type.hpp>
#include <pyrite/math/utility.hpp>
#include <pyrite/math/vector/vector_fwd.hpp>

namespace pyrite::math
{
template <typename T>
class vector<T, 3>
{
public:
  /****************************************************************************
   * assertion
   ****************************************************************************/
  static_assert(std::is_floating_point_v<T>);

  /****************************************************************************
   * type alias
   ****************************************************************************/
  using value_type = T; //!< type of vector element.

  /****************************************************************************
   * static constexpr value
   ****************************************************************************/
  static constexpr usize dimension = 3; //!< dimension of vector

  /****************************************************************************
   * constructor
   ****************************************************************************/
  /**
   * initialize all elements to zero.
   */
  constexpr vector() noexcept = default;

  /**
   * creates a vector whose elements have the specified values.
   * @param x x element.
   * @param y y element.
   * @param z z element.
   */
  constexpr vector(T x, T y, T z) : x{x}, y{y}, z{z} {}

  /**
   * copy constructor.
   * @param other source
   */
  constexpr vector(vector const& other) noexcept = default;

  /**
   * move constructor.
   * @param other source
   */
  constexpr vector(vector&& other) noexcept = default;

  /**
   * initialize from array.
   * @param v array
   */
  constexpr vector(T const (&v)[dimension]) : x{v[0]}, y{v[1]}, z{v[2]} {}

  /**
   * initialize from std::initializer_list.
   * @param other source
   */
  constexpr vector(std::initializer_list<T> const& ilist)
    : vector(ilist, std::make_index_sequence<dimension>{})
  {
  }

  /**
   * initialize from another vector type.
   */
  template <typename U>
  constexpr explicit vector(vector<U, dimension> const& other)
    : x{static_cast<T>(other.x)}
    , y{static_cast<T>(other.y)}
    , z{static_cast<T>(other.z)}
  {
  }

  /****************************************************************************
   * member function
   ****************************************************************************/
  /**
   * returns the dot product of two vectors.
   *
   * @param other the other vector.
   * @return the dot product.
   */
  constexpr T dot(vector const& other) const
  {
    return ::pyrite::math::dot(*this, other);
  }

  /**
   * returns the Euclidean distance between the two given points.
   *
   * @param other the first vector.
   * @return the distance.
   */
  constexpr T distance(vector const& other) const
  {
    return ::pyrite::math::distance(*this, other);
  }

  /**
   * returns the Euclidean distance between the two given points.
   *
   * @param other the other vector.
   * @return the distance.
   */
  constexpr T distance_squared(vector const& other) const
  {
    return ::pyrite::math::distance_squared(*this, other);
  }

  /**
   * returns the length of the this vector.
   *
   * @param the vector's length.
   */
  constexpr T length() const { return ::pyrite::math::length(*this); }

  /**
   * returns the length of the this vector squared.
   *
   * @param the vector's length.
   */
  constexpr T length_squared() const
  {
    return ::pyrite::math::length_squared(*this);
  }

  /**
   * normalize itself and return reference to its.
   *
   * @return the reference to this.
   */
  constexpr vector& normalize() { return ::pyrite::math::normalize(*this); }

  /**
   * returns normalized this vector.
   *
   * @return the normalized this vector.
   */
  constexpr vector normalized() const
  {
    return ::pyrite::math::normalized(*this);
  }

  /****************************************************************************
   * operator
   ****************************************************************************/
  /**
   * access specified element.
   *
   * @param  index index of the element to return.
   * @return reference to the requested element.
   */
  constexpr T& operator[](usize index)
  {
    assert(0 <= index || index <= 2);
    if (index == 0)
    {
      return x;
    }
    else if (index == 1)
    {
      return y;
    }
    else
    {
      return z;
    }
  }

  /**
   * access specified element.
   *
   * @param  index index of the element to return.
   * @return const reference to the requested element.
   */
  constexpr T const& operator[](usize index) const
  {
    assert(0 <= index || index <= 2);
    if (index == 0)
    {
      return x;
    }
    else if (index == 1)
    {
      return y;
    }
    else
    {
      return z;
    }
  }

  /**
   * copy assignment operator.
   *
   * @param other source.
   * @return *this
   */
  constexpr vector& operator=(vector const& other)
  {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  /**
   * move assignment operator.
   *
   * @param other source.
   * @return *this
   */
  constexpr vector& operator=(vector&& other)
  {
    x = std::move(other.x);
    y = std::move(other.y);
    z = std::move(other.z);
    return *this;
  }

private:
  /****************************************************************************
   * private constructor
   ****************************************************************************/
  /**
   * construct from std::initializer_list
   */
  template <std::size_t... Index>
  constexpr vector(std::initializer_list<T> const& ilist,
                   std::index_sequence<Index...>)
    : x{get_initializer_list_element(ilist, 0)}
    , y{get_initializer_list_element(ilist, 1)}
    , z{get_initializer_list_element(ilist, 2)}
  {
  }

  static constexpr T
    get_initializer_list_element(std::initializer_list<T> const& ilist,
                                 std::size_t                     index)
  {
    return index < ilist.size() ? (*(ilist.begin() + index)) : T{0};
  }

public:
  /****************************************************************************
   * member variable
   ****************************************************************************/
  T x = T{0};
  T y = T{0};
  T z = T{0};
};
} // namespace pyrite::math

#endif // PYRITE_MATH_VECTOR_VECTOR3_HPP
