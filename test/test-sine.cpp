/*
 * test
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

#include "test_config.hpp"

using test_config::dat_dir;
using test_config::ref_dat_dir;
using test_config::t_arr_fname;
using test_config::x_arr_fname;

//* setup
const std::string test_name = "test-sine";
const std::string dat_prefix = dat_dir + "/" + test_name + "-";
const std::string ref_dat_prefix = ref_dat_dir + "/" + test_name + "-";

constexpr size_t t_dim = 1000;
constexpr Real_T f = 1;
constexpr Real_T h = 1. / (t_dim - 1);

#ifdef __USE_SINGLE_PRECISION__
constexpr Real_T error_thres = 1e-6;
#else
constexpr Real_T error_thres = 1e-14;
#endif

int
main()
{
	//* 1. read the reference data
	Real_T t_arr_chk[t_dim];
	Real_T x_arr_chk[t_dim];
	matrix_rw::read<t_dim, 1>(ref_dat_prefix + t_arr_fname, t_arr_chk);
	matrix_rw::read<t_dim, 1>(ref_dat_prefix + x_arr_fname, x_arr_chk);

	//* 2. test
	Real_T t_arr[t_dim];
	Real_T x_arr[t_dim];

	for (size_t i = 0; i < t_dim; ++i) {
		t_arr[i] = i * h;
	}
	const auto start = std::chrono::high_resolution_clock::now();
	template_cpp_project::sine(f, t_arr, x_arr); //* <--- testing
	test_config::print_elapsed_since(start);

	//* 3. write the test data
	matrix_rw::write<t_dim, 1>(dat_prefix + t_arr_fname, t_arr);
	matrix_rw::write<t_dim, 1>(dat_prefix + x_arr_fname, x_arr);

	//* 4. verify the results
	Real_T t_max_error = test_config::compute_max_error<t_dim, 1>(t_arr, t_arr_chk);
	Real_T x_max_error = test_config::compute_max_error<t_dim, 1>(x_arr, x_arr_chk);

	if (t_max_error < error_thres && x_max_error < error_thres) {
		return 0;
	} else {
		std::cout << "t_max_error = " << t_max_error << std::endl;
		std::cout << "x_max_error = " << t_max_error << std::endl;
		return 1;
	}
}
