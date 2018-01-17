/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_RANDOM_RANDOM_STATE_HPP
#define PYRITE_RANDOM_RANDOM_STATE_HPP

#include <pyrite/core/type.hpp>

namespace pyrite
{
/**
 * State of pyrite::random
 */
struct random_state
{
  u64 seed{0u}; //!< seed
  u64 count{0u}; //!< count of generated random number.
};

/**
 * compares random_state objects
 */
bool operator==(random_state const& lhs, random_state const& rhs) noexcept
{
  return lhs.seed == rhs.seed && lhs.count == rhs.count;
}

/**
 * compares random_state objects
 */
bool operator!=(random_state const& lhs, random_state const& rhs) noexcept
{
  return !(lhs == rhs);
}
} // namespace pyrite

#endif // PYRITE_RANDOM_RANDOM_STATE_HPP
