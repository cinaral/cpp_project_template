#include "matrix_op.hpp"
#include "matrix_rw.hpp"
#include "template_cpp_project.hpp"
#include <string>
#include <chrono>
#include <cstdio>

using template_cpp_project::Real_T;
using template_cpp_project::size_t;

namespace test_config
{
const std::string dat_dir = "../dat";                       //* temporary data directory
const std::string ref_dat_dir = "../../test/reference_dat"; //* reference data directory
const std::string t_arr_fname = "t_arr.dat";                //* file name for the time array
const std::string x_arr_fname = "x_arr.dat";                //* file name for the x array

template <size_t T_DIM, size_t X_DIM>
Real_T
compute_max_error(const Real_T (&arr)[T_DIM * X_DIM], const Real_T (&arr_ref)[T_DIM * X_DIM])
{
	Real_T max_error = 0.;

	for (size_t i = 0; i < T_DIM; ++i) {
		const Real_T(&a)[X_DIM] = *matrix_op::select_row<T_DIM, X_DIM>(i, arr);
		const Real_T(&a_ref)[X_DIM] = *matrix_op::select_row<T_DIM, X_DIM>(i, arr_ref);

		for (size_t j = 0; j < X_DIM; ++j) {
			const Real_T error = std::abs(a[j] - a_ref[j]);

			if (error > max_error) {
				max_error = error;
			}
		}
	}
	return max_error;
}
//* setup
using namespace test_config;
const std::string test_name = "sine-test";
const std::string dat_prefix = dat_dir + "/" + test_name + "-";
const std::string ref_dat_prefix = ref_dat_dir + "/" + test_name + "-";

#ifdef USE_SINGLE_PRECISION
constexpr Real_T error_thres = 1e-6;
#else
constexpr Real_T error_thres = 1e-14;
#endif

constexpr size_t t_dim = 1000;
constexpr Real_T f = 1;
constexpr Real_T h = 1. / (t_dim - 1);

int
main()
{
	//* 1. read the reference data
	Real_T t_arr_ref[t_dim][1];
	Real_T x_arr_ref[t_dim][1];
	matrix_rw::read<t_dim, 1>(ref_dat_prefix + t_arr_fname, t_arr_ref);
	matrix_rw::read<t_dim, 1>(ref_dat_prefix + x_arr_fname, x_arr_ref);

	//* 2. test
	Real_T t_arr[t_dim][1];
	Real_T x_arr[t_dim][1];

	for (size_t i = 0; i < t_dim; ++i) {
		t_arr[i][0] = i * h;
	}

	const auto start_tp = std::chrono::high_resolution_clock::now();

	template_cpp_project::sine(f, t_arr, x_arr); //* <--- testing

	const auto now_tp = std::chrono::high_resolution_clock::now();
	const auto since_start_us =
	    std::chrono::duration_cast<std::chrono::microseconds>(now_tp - start_tp);
	printf("%zu us\n", since_start_us.count());

	//* 3. write the test data
	matrix_rw::write<t_dim, 1>(dat_prefix + t_arr_fname, t_arr);
	matrix_rw::write<t_dim, 1>(dat_prefix + x_arr_fname, x_arr);

	//* 4. verify the results
	Real_T max_error = 0.;

	for (size_t i = 0; i < t_dim; ++i) {
		const Real_T(&a)[1] = x_arr[i];
		const Real_T(&a_ref)[1] = x_arr_ref[i];
		const Real_T error = std::abs(a[0] - a_ref[0]);

		if (error > max_error) {
			max_error = error;
		}
	}

	if (max_error < error_thres) {
		return 0;
	} else {
		printf("x_max_error = %.3g\n", max_error);
		return 1;
	}
}
