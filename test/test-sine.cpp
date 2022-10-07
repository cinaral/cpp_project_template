/*
 * template_cpp_project
 *  
 * MIT License
 * 
 * Copyright (c) 2022 cinaral
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

#include "matrix_rw.hpp"
#include "template_cpp_project.hpp"
#include <chrono>

using uint_t = template_cpp_project::uint_t;
using real_t = template_cpp_project::real_t;

//* setup
const std::string dat_dir = "../dat";
const std::string ref_dat_dir = "../../test/reference_dat";
const std::string test_name = "test-sine";
const std::string dat_prefix = dat_dir + "/" + test_name + "-";
const std::string ref_dat_prefix = ref_dat_dir + "/" + test_name + "-";
const std::string t_arr_fname = "t_arr.dat";
const std::string x_arr_fname = "x_arr.dat";

constexpr uint_t t_dim = 1000;
constexpr real_t f = 1;
constexpr real_t h = 1. / (t_dim - 1);

#ifdef __USE_SINGLE_PRECISION__
constexpr real_t error_thres = 1e-6;
#else
constexpr real_t error_thres = 1e-14;
#endif

void print_elapsed_since(const std::chrono::time_point<std::chrono::high_resolution_clock> &start);

int
main()
{
	//* read reference data
	real_t t_arr_chk[t_dim];
	real_t x_arr_chk[t_dim];
	matrix_rw::read<t_dim, 1>(ref_dat_prefix + t_arr_fname, t_arr_chk);
	matrix_rw::read<t_dim, 1>(ref_dat_prefix + x_arr_fname, x_arr_chk);

	//* test
	real_t t_arr[t_dim] = {};
	real_t x_arr[t_dim] = {};

	for (uint_t i = 0; i < t_dim; ++i) {
		t_arr[i] = i * h;
	}

	const auto start = std::chrono::high_resolution_clock::now();

	template_cpp_project::sine(f, t_arr, x_arr);

	print_elapsed_since(start);

	//* write test data
	matrix_rw::write<t_dim, 1>(dat_prefix + t_arr_fname, t_arr);
	matrix_rw::write<t_dim, 1>(dat_prefix + x_arr_fname, x_arr);

	//* verify
	real_t t_max_error = 0.;
	real_t x_max_error = 0.;

	for (uint_t i = 0; i < t_dim; ++i) {
		real_t t_error = std::abs(t_arr[i] - t_arr_chk[i]);

		if (t_error > t_max_error) {
			t_max_error = t_error;
		}

		real_t x_error = std::abs(x_arr[i] - x_arr_chk[i]);
		if (x_error > x_max_error) {
			x_max_error = x_error;
		}
	}

	if (t_max_error < error_thres && x_max_error < error_thres) {
		return 0;
	} else {
		return 1;
	}
}

void
print_elapsed_since(const std::chrono::time_point<std::chrono::high_resolution_clock> &start)
{
	const auto end = std::chrono::high_resolution_clock::now();
	const auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "elapsed (us): " << diff.count() << std::endl;
}
