/**
 * @file
 * @author    block
 * @copyright (c) 2018 block.
 */

#ifndef PYRITE_MPL_TYPE_LIST_TYPE_LIST_HPP
#define PYRITE_MPL_TYPE_LIST_TYPE_LIST_HPP

#include <pyrite/core/mpl/type_list.hpp>

namespace pyrite::mpl
{
using pyrite::core::mpl::type_list;

using signed_integer_type_list = type_list<signed char,
                                      signed short,
                                      signed long,
                                      signed long long,
                                      signed int>;

using unsigned_integer_type_list = type_list<unsigned char,
                                        unsigned short,
                                        unsigned long,
                                        unsigned long long,
                                        unsigned int>;

using floating_point_list = type_list<float, double, long double>;
} // namespace pyrite::mpl
#endif // PYRITE_MPL_TYPE_LIST_TYPE_LIST_HPP
