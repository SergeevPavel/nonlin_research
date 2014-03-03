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
using namespace std;

int main()
{
	Timer timer;

	Ode<1> ode{f3, {1}, 0.0, 1.0, 0.02};
	Point<1> y0{1};
	Solver<1> slv1;
	Solution<1> solution = slv1.Solve(f3, y0, 0.0, 1.0, 0.02);

	double max = 0;
	double t;
	double diff;
	for (int i = 0; i < solution.nodesCount; i++)
	{
		t = i*solution.step;
		diff = fabs(solution[i][0] - (pow(t,2)/2 + 1));
		if (diff > max)
			max = diff;
	}
	std::cout << "max deviation = " << max << std::endl;
	return 0;
}


