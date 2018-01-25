#ifndef PYRITE_MPL_TYPE_PAIR_HPP
#define PYRITE_MPL_TYPE_PAIR_HPP

namespace pyrite::mpl
{
template <typename First, typename Second>
struct type_pair
{
  using first  = First;
  using second = Second;
};
} // namespace pyrite::mpl

#endif // PYRITE_MPL_TYPE_PAIR_HPP
