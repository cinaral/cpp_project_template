/*
 * cpp_project_template
 *
 * MIT License
 *
 * Copyright (c) 2022 Cinar, A. L.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SINE_HPP_CINARAL_220923_1711
#define SINE_HPP_CINARAL_220923_1711

#include "types.hpp"
#include <cmath>
#include <cstdio>

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
			x_arr[i][j] = sin(pow(t_arr[i][0], j) * 2 * M_PI * base_freq);
		}
	}
}

} // namespace cpp_project_template

#endif
