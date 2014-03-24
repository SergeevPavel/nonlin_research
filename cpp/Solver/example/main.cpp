#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

#include "solver.h"
#include "example.h"

using namespace std;

int main()
{
	Timer timer;

	Ode<1> ode{f3, {1}, 0.0, 1.0, 0.02};
	Point<1> y0{1};
	Solver<1> solver;
	Solution<1> solution = solver.Solve(ode);

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


