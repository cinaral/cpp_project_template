/* Copyright 2022-2023, Cinar, A. L.
 * SPDX-License-Identifier: MIT
 */

#ifndef SINE_HPP_CINARAL_220923_1711
#define SINE_HPP_CINARAL_220923_1711

#include "types.hpp"
#include <cmath>
#include <cstdio>
#include <vector>
#include <array>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

namespace cpp_project_template
{
/* ```make_signal<S>(base_freq, signal)```
 * Generates a signal with `S` sine waves but with a twist
 */
template <Size S>
void
make_signal(const std::vector<std::array<Real, 1>> &t_arr, std::vector<std::array<Real, S>> &x_arr,
            const Real base_freq = 1.0)
{
	const Size t_dim = t_arr.size();

	for (Size i = 0; i < t_dim; ++i) {
		for (Size j = 0; j < S; ++j) {
			x_arr[i][j] = sin(pow(t_arr[i][0], (j + 1)) * 2 * M_PI * base_freq);
		}
	}
}

} // namespace cpp_project_template

#endif
