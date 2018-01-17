#ifndef PYRITE_RANDOM_RANDOM_INL
#define PYRITE_RANDOM_RANDOM_INL

#include <cassert>
#include <limits>
#include <type_traits>

#include <pyrite/core/type.hpp>
#include <pyrite/mpl/false_v.hpp>
#include <pyrite/random/random.hpp>

namespace pyrite
{
///
// consructor
///
random::random()
  : state_{static_cast<seed_type>(random_device()), 0u}, engine_{state_.seed}
{
}

random::random(random::seed_type seed) : state_{seed, 0u}, engine_{seed} {}
random::random(random const& other)
  : state_{other.state_}, engine_{other.state_.seed}
{
  engine_.discard(state_.count);
}

random::random(random&& other)
  : state_{std::move(other.state_)}, engine_{std::move(other.engine_)}
{
}

///
// member function
///
template <typename T>
auto random::next()
{
  if constexpr (std::is_integral_v<T>)
  {
    auto const min = std::numeric_limits<T>::min();
    auto const max = std::numeric_limits<T>::max();
    return next(min, max);
  }
  else if constexpr (std::is_floating_point_v<T>)
  {
    auto const min = T(0);
    auto const max = T(1);
    return next(min, max);
  }
  else
  {
    static_assert(mpl::false_v<T>, "not support");
  }
}

template <typename T>
auto random::next(T const& min, T const& max)
{
  assert(min < max);

  state_.count++;

  if constexpr (std::is_integral_v<T>)
  {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(engine_);
  }
  else if constexpr (std::is_floating_point_v<T>)
  {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(engine_);
  }
  else
  {
    static_assert(mpl::false_v<T>, "not support");
  }
}

random::seed_type random::seed() const noexcept { return state_.seed; }

random_state random::state() const noexcept { return state_; }

void random::discard(u64 count)
{
  engine_.discard(static_cast<unsigned long long>(count));
  state_.count += count;
}

void random::reset() { reset(state_.seed); }

void random::reset(random::seed_type seed) { reset(random_state{seed, 0u}); }

void random::reset(random_state const& state)
{
  state_ = state;
  engine_.seed(state_.seed);
  engine_.discard(state_.count);
}

///
// operator
///
bool random::operator==(random const& rhs) const noexcept
{
  return state_ == rhs.state_;
}

bool random::operator!=(random const& rhs) const noexcept
{
  return !(*this == rhs);
}

random& random::operator=(random const& rhs)
{
  if (this != &rhs)
  {
    reset(rhs.state_);
  }

  return *this;
}

random& random::operator=(random&& rhs)
{
  if (this != &rhs)
  {
    state_  = std::move(rhs.state_);
    engine_ = std::move(rhs.engine_);
  }
  return *this;
}
} // namespace pyrite

#endif // PYRITE_RANDOM_RANDOM_INL
