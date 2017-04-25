/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_CORE_VOID_T_HPP
#define PYRITE_CORE_VOID_T_HPP

namespace pyrite
{
/**
 * Utility meta function that maps a sequence of any types to the type void.
 */
template <typename... Args>
using void_t = void;
} // namespace pyrite

#endif // PYRITE_CORE_VOID_T_HPP
