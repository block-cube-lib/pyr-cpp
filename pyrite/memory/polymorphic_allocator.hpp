#ifndef PYRITE_MEMORY_POLYMORPHIC_ALLOCATOR_HPP
#define PYRITE_MEMORY_POLYMORPHIC_ALLOCATOR_HPP

#if __has_include(<memory_resource>)
#  include <memory_resource>

namespace pyrite::memory
{
template <typename T>
using polymorphic_allocator = std::pmr::polymorphic_allocator;
} // namespace pyrite::memory

#  elif __has_include(<experimental/memory_resource>
namespace pyrite::memory
{
template <typename T>
using polymorphic_allocator = std::experimental::pmr::polymorphic_allocator;
} // namespace pyrite::memory
#  else  // __has_include
namespace pyrite::memory
{
template <typename T>
class polymorphic_allocator
{
};
} // namespace pyrite::memory
#  endif // __has_include
#endif   // PYRITE_MEMORY_POLYMORPHIC_ALLOCATOR_HPP
