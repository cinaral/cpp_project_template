/* Copyright 2026, Cinar, A. L.
 * SPDX-License-Identifier: GPL-3.0-only
 */
 
#ifndef DEFINES_HPP_CINARAL_230331_1524
#define DEFINES_HPP_CINARAL_230331_1524

#include <cstddef>

namespace cpp_project_template
{
using Size = std::size_t;
#ifdef USE_SINGLE_PRECISION
using Real = float;
#else
using Real = double;
#endif
} // namespace cpp_project_template
#endif
