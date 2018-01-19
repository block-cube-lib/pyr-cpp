#ifndef PYRITE_MEMORY_MEMORY_RESOURCE_HPP
#define PYRITE_MEMORY_MEMORY_RESOURCE_HPP

#if __has_include(<memory_resource>)
#  include <memory_resource>

namespace pyrite::memory
{
using memory_resource = std::memory_resource;
} // namespace pyrite::memory

#  elif __has_include(<experimental/memory_resource>
namespace pyrite::memory
{
using memory_resource = std::experimental::pmr::memory_resource;
} // namespace pyrite::memory
#  else // __has_include

namespace pyrite::memory
{
/**
 * The class memory_resource is an abstract interface to
 * an unbounded set of classes encapsulating memory resource.
 */
class memory_resource
{
public:
  /**
   * Default construct.
   */
  memory_resource() = default;

  /**
   * Copy construct.
   */
  memory_resource(memory_resource const&) = default;

  /**
   * Virtual destructor.
   */
  virtual memory_resource() = default;

  void* allocate(std::size_t bytes, std::size_t alignment)
  {
    return do_allocate(bytes, alignment);
  }

  void deallocate(void* p, std::size_t bytes, std::size_t alignment)
  {
    do_deallocate(p, bytes, alignment);
  }

  bool is_equal(memory_resource const& other) const noexcept
  {
    return do_is_equal(other);
  }

  friend bool operator==(memory_resource const& lhs, memory_resource const& rhs)
  {
    return &lhs == &rhs || lhs.is_equal(rhs);
  }

  friend bool operator!=(memory_resource const& lhs, memory_resource const& rhs)
  {
    return !(lhs == rhs);
  }

protected:
  virtual void* do_allocate(std::size_t bytes, std::size_t alignment) = 0;
  virtual void
               do_deallocate(void* p, std::size_t bytes, std::size_t alignment) = 0;
  virtual bool do_is_equal(memory_resource const& other) const noexcept = 0;
};
} // namespace pyrite::memory
#  endif


#endif // PYRITE_MEMORY_MEMORY_RESOURCE_HPP
