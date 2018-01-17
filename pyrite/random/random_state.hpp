#ifndef PYRITE_RANDOM_RANDOM_STATE_HPP
#define PYRITE_RANDOM_RANDOM_STATE_HPP

#include <pyrite/core/type.hpp>

namespace pyrite
{
struct random_state
{
  u64 seed{0u};
  u64 count{0u};
};

bool operator==(random_state const& lhs, random_state const& rhs) noexcept
{
  return lhs.seed == rhs.seed && lhs.count == rhs.count;
}

bool operator!=(random_state const& lhs, random_state const& rhs) noexcept
{
  return !(lhs == rhs);
}
} // namespace pyrite

#endif // PYRITE_RANDOM_RANDOM_STATE_HPP
