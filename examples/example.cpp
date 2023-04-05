#include <cpp_project_template.hpp>
#include <matrix_rw.hpp>

using Real = cpp_project_template::Real;
using Size = cpp_project_template::Size;

constexpr Size t_size = 100;
constexpr Size x_dim = 3;

int
main(int, char *[])
{
	std::vector<std::array<Real, 1>> t_arr(t_size);
	for (Size i = 0; i < t_size; ++i) {
		t_arr[i][0] = static_cast<Real>(i) / t_size;
	}

	std::vector<std::array<Real, x_dim>> x_arr(t_size);
	cpp_project_template::make_signal(t_arr, x_arr);

	matrix_rw::Writer<1> write_t_arr;
	write_t_arr("../data/t_arr.csv", t_arr);

	matrix_rw::Writer<x_dim> write_x_arr;
	write_x_arr("../data/x_arr.csv", x_arr);

	return 0;
}
