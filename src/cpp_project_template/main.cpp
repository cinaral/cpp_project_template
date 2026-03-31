/* Copyright 2026, Cinar, A. L.
 * SPDX-License-Identifier: GPL-3.0-only
 */
 
#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXd;

int
main()
{
	MatrixXd m(2, 2);
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);
	std::cout << m << std::endl;
}
