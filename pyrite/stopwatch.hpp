/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_STOPWATCH_HPP
#define PYRITE_STOPWATCH_HPP

#include <chrono>

namespace pyrite
{
/**
 * Class stopwatch measures elapsed time.
 */
class stopwatch
{
private:
  using nanoseconds = std::chrono::nanoseconds;              // nanoseconds type
  using time_point  = std::chrono::steady_clock::time_point; // time_point type

public:
  /**
   * Default constructor.
   * start measures.
   */
  stopwatch() noexcept { restart(); }

  /**
   * Copy constructor.
   * generated by the compiler.
   */
  stopwatch(stopwatch const&) noexcept = default;

  /**
   * Move constructor.
   * generated by the compiler.
   */
  stopwatch(stopwatch&&) noexcept = default;

  /**
   * Destructor.
   * generated by the compiler.
   */
  ~stopwatch() = default;

  /**
   * Stop time interval measurement and resets the elapsed time to zero.
   */
  void reset()
  {
    nanoseconds_ = nanoseconds{0};
    is_running_  = false;
  }

  /**
   * Starts, or resumes, measuring elapsed time for an interval.
   */
  void start()
  {
    if (!is_running())
    {
      start_time_point_ = std::chrono::steady_clock::now();
      is_running_       = true;
    }
  }

  /**
   * reset() and start()
   */
  void restart()
  {
    reset();
    start();
  }

  /**
   * Stops measuring elapsed time for an interval.
   */
  void stop()
  {
    if (is_running())
    {
      nanoseconds_ += from_started();
      is_running_ = false;
    }
  }

  /**
   * Indicating whether the stopwatch timer is running.
   */
  bool is_running() const noexcept { return is_running_; }

  /**
   * Get the total elapsed time.
   * @tparam Duration Result type.
   * @return Total elapsed time.
   */
  template <typename Duration>
  typename Duration::rep elapsed() const noexcept
  {
    auto const count = nanoseconds_ + from_started();
    return std::chrono::duration_cast<Duration>(count).count();
  }

  /**
   * Get total elapsed time seconds.
   * @tparam T Result type
   * @return Total elapsed time seconds.
   */
  template <typename T>
  T elapsed_seconds() const noexcept
  {
    using result_t = std::chrono::duration<T, std::ratio<1, 1>>;
    return elapsed<result_t>();
  }

  /**
   * Get total elapsed time milliseconds.
   * @tparam T result type
   * @return Total elapsed time milliseconds.
   */
  template <typename T>
  T elapsed_milliseconds() const noexcept
  {
    using result_t = std::chrono::duration<T, std::ratio<1, 1000>>;
    return elapsed<result_t>();
  }

  /**
   * Copy assignment operator.
   * generated by the compiler.
   */
  stopwatch& operator=(stopwatch const&) = default;

  /**
   * Move assignment operator.
   * generated by the compiler.
   */
  stopwatch& operator=(stopwatch&&) = default;

private:
  /**
   * Get nanoseconds from at last start.
   * @return from at last start or 0 if stopwatch timer is running.
   */
  nanoseconds from_started() const noexcept
  {
    if (is_running())
    {
      auto const now      = std::chrono::steady_clock::now();
      auto const duration = now - start_time_point_;
      return std::chrono::duration_cast<nanoseconds>(duration);
    }
    else
    {
      return nanoseconds{0};
    }
  }

private:
  nanoseconds nanoseconds_{0};     // Sum nanoseconds between start and stop.
  time_point  start_time_point_{}; // time time point at last start.
  bool is_running_{false}; // Indicating whether the stopwatch timer is running.
};
} // namespace pyrite
#endif // PYRITE_STOPWATCH_HPP
