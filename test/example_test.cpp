#include "cpp_project_template.hpp"
#include "matrix_rw.hpp"
#include <chrono>
#include <cstdio>
#include <limits> /** std::numeric_limits */
#include <string>

using cpp_project_template::Real;
using cpp_project_template::Size;

/** relative to the directory of the executable */
const std::string test_name = "example_test";
const std::string fprefix = "../data/" + test_name + "-";
const std::string ref_fprefix = "../../test/ref_data/" + test_name + "-";
const std::string t_arr_fname = "t_arr.csv";
const std::string x_arr_fname = "x_arr.csv";

constexpr Real error_threshold = 1e2 *std::numeric_limits<Real>::epsilon();
constexpr Size t_size_default = 100;
constexpr Size x_dim = 3;
constexpr Real base_freq = 1.;

int
main()
{
	/** 1. read the reference data */
	std::vector<std::array<Real, 1>> ref_t_arr;
	ref_t_arr.reserve(t_size_default);
	matrix_rw::Reader<1> read_t_arr;
	read_t_arr(ref_fprefix + t_arr_fname, ref_t_arr);
	const Size t_size = ref_t_arr.size();
	
	std::vector<std::array<Real, x_dim>> ref_x_arr;
	ref_x_arr.reserve(t_size);
	matrix_rw::Reader<x_dim> read_x_arr;
	read_x_arr(ref_fprefix + x_arr_fname, ref_x_arr);

	/** 2. test */
	std::vector<std::array<Real, x_dim>> x_arr(t_size);
	cpp_project_template::make_signal(ref_t_arr, x_arr, base_freq);

	/** 3. write the test data */
	matrix_rw::Writer<x_dim> write_x_arr;
	write_x_arr(fprefix + x_arr_fname, x_arr);

	//* 4. verify the results
	Real max_error = 0.;

	for (size_t i = 0; i < t_size; ++i) {
		for (size_t j = 0; j < x_dim; ++j) {
			const Real error = std::abs(x_arr[i][j] - ref_x_arr[i][j]);

			if (error > max_error) {
				max_error = error;
			}
		}
	}

	if (max_error < error_threshold) {
		return 0;
	} else {
		printf("Maximum Error: %8.4g\n", max_error);
		return 1;
	}
}
