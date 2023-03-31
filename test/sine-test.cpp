#include "test_config.hpp"

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
	Real_T t_arr_ref[t_dim];
	Real_T x_arr_ref[t_dim];
	matrix_rw::read<t_dim, 1>(ref_dat_prefix + t_arr_fname, t_arr_ref);
	matrix_rw::read<t_dim, 1>(ref_dat_prefix + x_arr_fname, x_arr_ref);

	//* 2. test
	Real_T t_arr[t_dim];
	Real_T x_arr[t_dim];

	for (size_t i = 0; i < t_dim; ++i) {
		t_arr[i] = i * h;
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
	Real_T t_max_error = compute_max_error<t_dim, 1>(t_arr, t_arr_ref);
	Real_T x_max_error = compute_max_error<t_dim, 1>(x_arr, x_arr_ref);

	if (t_max_error < error_thres && x_max_error < error_thres) {
		return 0;
	} else {
		printf("t_max_error = %.3g\n", t_max_error);
		printf("x_max_error = %.3g\n", x_max_error);
		return 1;
	}
}
