/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_RANDOM_RANDOM_INL
#define PYRITE_RANDOM_RANDOM_INL

#include <cassert>
#include <chrono>
#include <limits>
#include <type_traits>

#include <pyrite/mpl/false_v.hpp>

namespace pyrite
{
///
// consructor
///
random::random() : random(random_state{generate_seed(), 0u}) {}

random::random(random_state const& state) : state_{state}, engine_{state.seed}
{
  engine_.discard(state_.count);
}

random::random(random::seed_type seed) : random{random_state{seed, 0u}} {}

random::random(random const& other) : random{other.state_} {}

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

void random::discard(u64 z)
{
  engine_.discard(static_cast<unsigned long long>(z));
  state_.count += z;
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

random::seed_type random::generate_seed()
{
  // get count from epoch time
  static auto const get_now = []() {
    auto now = std::chrono::steady_clock::now();
    return static_cast<unsigned long long>(now.time_since_epoch().count());
  };

  // initialize engine
  static thread_local std::mt19937_64 engine{
    static_cast<std::mt19937_64::result_type>(std::random_device{}() &
                                              get_now())};

  engine.discard(get_now() & 0x0f);
  return static_cast<seed_type>(engine());
}
} // namespace pyrite

#endif // PYRITE_RANDOM_RANDOM_INL
