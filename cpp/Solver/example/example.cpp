#include <cmath>

#include "solver.h"
#include "example.h"

Point<1> f1(Point<1> y, double t) /* Problem1 f1: y' = t */
{
	Point<1> fy;
	fy[0] = t;
	return fy;
};

Point<1> u1(double t) /* Solution1 y = x^2 + 1 */
{
	return {(t * t) / 2.0 + 1.0};
}

void test1()
{
	Timer timer;
	Solver<1> solver;
	Ode<1> ode{f1, {1}, 0.0, 1.0, 100};
	Solution<1> solution = solver.Solve(ode);
	double max = 0;
	double t;
	double diff;
	for (int i = 0; i < solution.nodesCount; i++)
	{
		t = i*solution.step;
		diff = (solution[i] - u1(t)).abs();
		max = std::max(diff, max);
	}
	std::cout << "max deviation = " << max << std::endl;
}

Point<1> f2(Point<1> y, double t) /* f3: y' = t + y */
{
	Point<1> fy;
	fy = y + t;
	return fy;
};

Point<1> u2(double t)
{
	return {exp(t) - t - 1};
};

void test2()
{
	Timer timer;
	Solver<1> solver;
	Ode<1> ode{f2, {0.0}, 0.0, 1.0, 100};
	Solution<1> solution = solver.Solve(ode);
	double max = 0;
	double t;
	double diff;
	for (int i = 0; i < solution.nodesCount; i++)
	{
		t = i*solution.step;
		diff = (solution[i] - u2(t)).abs();
		max = std::max(diff, max);
	}
	std::cout << "max deviation = " << max << std::endl;
}