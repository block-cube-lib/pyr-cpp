#ifndef PYRITE_CORE_ENDIAN_HPP
#define PYRITE_CORE_ENDIAN_HPP

namespace pyrite
{
inline namespace core
{
enum class endian
{
  little,
  big,

  native =
#if __BIG_ENDIAN__
    big
#elif __LITTLE_ENDIAN__
    little
#elif defined(__BYTE_ORDER__)
#  if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    big
#  elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    little
#  endif
#endif
};
} // namespace core
} // namespace pyrite

#endif // PYRITE_CORE_ENDIAN_HPP
