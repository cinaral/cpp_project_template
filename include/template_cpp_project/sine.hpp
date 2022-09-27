#ifndef SINE_HPP_CINARAL_220923_1711
#define SINE_HPP_CINARAL_220923_1711

#include "types.hpp"
#include <cmath>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

namespace template_cpp_project
{
//* generates a sine wave.
//*
//* inputs:
//* 1. f - frequency
//* 2. t_arr - [T_DIM] input time array
template <uint_t T_DIM>
void
sine(const real_t f, const real_t (&t_arr)[T_DIM], real_t (&x_arr)[T_DIM])
{
	for (uint_t i = 0; i < T_DIM; ++i) {
#ifdef __USE_SINGLE_PRECISION__
		x_arr[i] = sinf(t_arr[i] * 2 * M_PI * f);
#else
		x_arr[i] = sin(t_arr[i] * 2 * M_PI * f);
#endif
	}
}

} // namespace template_cpp_project

#endif