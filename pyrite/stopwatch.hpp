/**
 * @file
 * @brief     Define noncopyable.
 *
 * @author    block
 *
 * @copyright 2016 block (c)copyright all rights reserved.
 */

#include <chrono>

namespace pyrite
{
class stopwatch
{
private:
  using nanoseconds = std::chrono::nanoseconds;              // nanoseconds type
  using time_point  = std::chrono::steady_clock::time_point; // time_point type

public:
  stopwatch() noexcept { restart(); }
  stopwatch( stopwatch const& ) noexcept = default;
  stopwatch( stopwatch&& ) noexcept      = default;
  ~stopwatch()                           = default;

  void restart() noexcept
  {
    nanoseconds_             = nanoseconds{0};
    last_resumed_time_point_ = std::chrono::steady_clock::now();
    is_stoped_               = false;
  }

  void stop() noexcept
  {
    if( is_stoped() )
    {
      return;
    }

    nanoseconds_ += from_last_resume();
    is_stoped_ = true;
  }

  void resume() noexcept
  {
    if( is_stoped() )
    {
      last_resumed_time_point_ = std::chrono::steady_clock::now();
      is_stoped_               = false;
    }
  }

  bool is_stoped() const noexcept { return is_stoped_; }

  template <typename Duration>
  typename Duration::rep elapsed() const noexcept
  {
    if( is_stoped() )
    {
      return std::chrono::duration_cast<Duration>( nanoseconds_ ).count();
    }
    else
    {
      auto const count = nanoseconds_ + from_last_resume();
      return std::chrono::duration_cast<Duration>( count ).count();
    }
  }

  template <typename T>
  T seconds() const noexcept
  {
    using result_t = std::chrono::duration<T, std::ratio<1, 1>>;
    return elapsed<result_t>();
  }

  stopwatch& operator=( stopwatch const& ) = default;
  stopwatch& operator=( stopwatch&& ) = default;

private:
  nanoseconds from_last_resume() const noexcept
  {
    auto const now      = std::chrono::steady_clock::now();
    auto const duration = now - last_resumed_time_point_;
    return std::chrono::duration_cast<nanoseconds>( duration );
  }

private:
  nanoseconds nanoseconds_{0};            // count nanoseconds
  time_point  last_resumed_time_point_{}; // time point
  bool        is_stoped_{false};
};
} // namespace pyrite
