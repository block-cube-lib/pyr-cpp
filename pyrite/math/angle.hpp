/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MATH_ANGLE_HPP
#define PYRITE_MATH_ANGLE_HPP

#include <pyrite/math/utility.hpp>

namespace pyrite::math
{

struct radian_angle_tag_t
{
};
constexpr radian_angle_tag_t radian_tag;

struct degree_angle_tag_t
{
};
constexpr degree_angle_tag_t degree_tag;

template <typename T>
class angle
{
public:
  /****************************************************************************
   * type alias
   ****************************************************************************/
  using value_type = T; //!< value type (T)

  /****************************************************************************
   * constructor / destructor
   ****************************************************************************/
  /**
   * default constructor.
   */
  constexpr angle() noexcept = default;

  /**
   * constructs the angle from radian.
   *
   * @param[in] rad radian.
   */
  constexpr angle(T const& rad, radian_angle_tag_t) : radian_{rad} {}

  /**
   * constructs the angle from degree.
   *
   * @param[in] deg degree.
   */
  constexpr angle(T const& deg, degree_angle_tag_t)
    : radian_{degree_to_radian(deg)}
  {
  }

  /**
   * copy constrcutor.
   *
   * @param[in] other source.
   */
  constexpr angle(angle const& other) : radian_(other.radian_) {}

  /**
   * move constrcutor.
   *
   * @param[in] other source.
   */
  constexpr angle(angle&& other) = default;

  /**
   * destructor.
   * generated form compiler.
   *
   * @param[in] other source.
   */
  ~angle() = default;

  /****************************************************************************
   * member function
   ****************************************************************************/
  /**
   * rotate angle object
   *
   * @param[in] other add angle.
   * @return reference
   */
  constexpr angle& rotate(angle const& other)
  {
    radian_ += other.radian_;
    return *this;
  }

  /**
   * set value form radian.
   *
   * @param[in] rad radian.
   * @return return the result by reference.
   */
  constexpr angle& radian(T const& rad)
  {
    radian_ = rad;
    return *this;
  }

  /**
   * set value from degree.
   *
   * @param[in] deg degree.
   * @return return the result by reference.
   */
  constexpr angle& degree(T const& deg)
  {
    radian_ = degree_to_radian(deg);
    return *this;
  }

  /**
   * get value of radian.
   * @return radian.
   */
  constexpr T radian() const noexcept { return radian_; }

  /**
   * get value of degree.
   * @return degree.
   */
  constexpr T degree() const noexcept { return radian_to_degree(radian_); }

  /**
   * get sin(radian()).
   * @return sin(radian()).
   */
  constexpr T sin() const { return ::pyrite::math::sin(radian_); }

  /**
   * get cos(radian()).
   * @return cos(radian()).
   */
  constexpr T cos() const { return ::pyrite::math::cos(radian_); }

  /**
   * get tan(radian()).
   * @return tan(radian()).
   */
  constexpr T tan() const { return ::pyrite::math::tan(radian_); }

  /****************************************************************************
   * member operator
   ****************************************************************************/
  /**
   * copy assignment operator.
   *
   * @param other source.
   * @return return the result by reference.
   */
  constexpr angle& operator=(angle const& other) noexcept
  {
    if (this != &other)
    {
      radian_ = std::move(other.radian_);
    }
    return *this;
  }

  /**
   * move assignment operator.
   *
   * @param other source.
   * @return return the result by reference.
   */
  constexpr angle& operator=(angle&& other) noexcept
  {
    if (this != &other)
    {
      radian_ = std::move(other.radian_);
    }
    return *this;
  }

  /****************************************************************************
   * friend operator
   ****************************************************************************/
  friend constexpr angle operator+(angle const& a) { return a; }
  friend constexpr angle operator-(angle const& a)
  {
    return {-a.radian_, radian_tag};
  }

  friend constexpr angle& operator+=(angle& lhs, angle const& rhs)
  {
    return lhs.rotate(rhs);
  }

  friend constexpr angle& operator-=(angle& lhs, angle const& rhs)
  {
    return lhs.rotate(-rhs);
  }

  friend constexpr angle& operator*=(angle& a, T const& value)
  {
    a.radian_ *= value;
    return a;
  }

  friend constexpr angle& operator/=(angle& a, T const& value)
  {
    a.radian_ /= value;
    return a;
  }

  friend constexpr angle operator+(angle const& lhs, angle const& rhs)
  {
    return {lhs.radian_ + rhs.radian_, radian_tag};
  }

  friend constexpr angle operator-(angle const& lhs, angle const& rhs)
  {
    return std::move(angle(lhs) -= rhs);
  }

  friend constexpr angle operator*(angle const& a, T const& value)
  {
    return std::move(angle(a) *= value);
  }

  friend constexpr angle operator/(angle const& a, T const& value)
  {
    return std::move(angle(a) /= value);
  }

  friend constexpr bool operator==(angle const& lhs, angle const& rhs) noexcept
  {
    return equal(lhs.radian_, rhs.radian_);
  }

  friend constexpr bool operator!=(angle const& lhs, angle const& rhs) noexcept
  {
    return !(rhs == lhs);
  }

  friend constexpr bool operator<(angle const& lhs, angle const& rhs) noexcept
  {
    return lhs.radian_ < rhs.radian_;
  }

  friend constexpr bool operator<=(angle const& lhs, angle const& rhs) noexcept
  {
    return (lhs == rhs) || (lhs < rhs);
  }

  friend constexpr bool operator>(angle const& lhs, angle const& rhs) noexcept
  {
    return !(lhs <= rhs);
  }

  friend constexpr bool operator>=(angle const& lhs, angle const& rhs) noexcept
  {
    return !(lhs < rhs);
  }

private:
  /****************************************************************************
   * member variable
   ****************************************************************************/
  T radian_ = T{0}; //!< radian
};
} // namespace pyrite::math

#endif // PYRITE_MATH_ANGLE_HPP
