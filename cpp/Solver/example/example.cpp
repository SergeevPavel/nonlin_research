#include <cmath>

#include "solver.h"
#include "example.h"

Point<1> f1(Point<1> y, double t) /* f1: y' = t */
{
	Point<1> fy;
	fy[0] = t;
	return fy;
};

void test1()
{
	Timer timer;
	Solver<1> solver;
	Ode<1> ode{f1, {1}, 0.0, 1.0, 0};
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
}

Point<1> f2(Point<1> y, double t) /* f2: y' = 2*y */
{
	Point<1> fy;
	fy = y*2.0;
	return fy;
};

Point<1> f3(Point<1> y, double t) /* f3: y' = t + y */
{
	Point<1> fy;
	fy = y + t;
	return fy;
};

Point<2> f4(Point<2> y, double t) /* f4: y'' + y - y^3 = 0 */
{
	Point<2> fy;
	fy[0] = y[1];
	fy[1] = pow(y[0],3) - y[0];
	return fy;
};

Point<2> f5(Point<2> y, double t) /* f5: y'' + y - (1 + 1.3cos(2t))y^3 */
{
	Point<2> fy;
	fy[0] = y[1];
	fy[1] = (1 + 1.3*cos(2*t)) * pow(y[0],3) - y[0];
	return fy;
};

Point<4> f6(Point<4> y, double t) /* system y[i] = t*y[i+1], dimension = 4 */
{
	Point<4> fy;
	fy[0] = t*y[1];
	fy[1] = t*y[2];
	fy[2] = t*y[3];
	fy[3] = t*y[0];
	return fy;
};