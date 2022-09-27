#ifndef TYPES_HPP_CINARAL_220926_2329
#define TYPES_HPP_CINARAL_220926_2329

namespace template_cpp_project
{
using uint_t = unsigned long long int;
#ifdef __USE_SINGLE_PRECISION__
using real_t = float;
#else
using real_t = double;
#endif
} // namespace template_cpp_project

#endif