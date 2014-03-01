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
	Timer timer;

	Ode<1> ode{f1, {1}, 0.0, 1.0, 0.01};
	Solver<1> slv1;
	Solution<1> solution = slv1.Solve(ode);

	double max = 0;
	for (int i = 0; i <= solution.nodesCount; i++)
	{
		double t = i*solution.step;
		double div = fabs(solution[i][0] - (5*pow(t,2.0)/2.0 + 1));
		std::cout << div << std::endl;
		if (div > max)
			max = div;
	}
	std::cout << "max div = " << div << std::endl;
	return 0;
}


