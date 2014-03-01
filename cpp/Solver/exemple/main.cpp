/*
 * main.cpp
 *
 *  Created on: Mar 1, 2014
 *      Author: mikhail
 */

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

#include "RKSolver.h"
#include "exemple.h"

using namespace RKSolver;

int main()
{
	Timer t;

	Ode<1> ode{f1, {1}, 0.0, 1.0, 0.1};
	Solver<1> slv1;
	Solution<1> solution = slv1.Solve(ode);
	std::cout<<solution;
	return 0;
}


