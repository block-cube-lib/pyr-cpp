#ifndef PYRITE_RANDOM_RANDOM_HPP
#define PYRITE_RANDOM_RANDOM_HPP

#include <random>

#include <pyrite/core/type.hpp>
#include <pyrite/random/random_state.hpp>

namespace pyrite
{
class random
{
public:
  using seed_type = decltype(random_state::seed);

  random();

  explicit random(seed_type seed);

  random(random const& other);

  random(random&& other);
  ~random() = default;

  template <typename T>
  auto next();

  template <typename T>
  auto next(T const& min, T const& max);

  seed_type seed() const noexcept;

  random_state state() const noexcept;

  void discard(u64 count);

  void reset();
  void reset(seed_type seed);
  void reset(random_state const& state);

  bool operator==(random const& rhs) const noexcept;

  bool operator!=(random const& rhs) const noexcept;

  random& operator=(random const& rhs);

  random& operator=(random&& rhs);

private:
  random_state    state_;
  std::mt19937_64 engine_;

  static thread_local inline std::random_device random_device;
};
} // namespace pyrite

#  include <pyrite/random/random.inl>

#endif // PYRITE_RANDOM_RANDOM_HPP
