#ifndef RKSOLVER_H_
#define RKSOLVER_H_


#include <cstring>
#include <iostream>
#include <initializer_list>

#include "point.h"
#include "solution.h"
#include "utils.h"

template <int d1>
class Solver
{
public:
	Solver(double i_upperBound = 10000000000000.0):
	upperBound(i_upperBound)
	{
	}

	Solution<d1> Solve(Ode<d1> ode)
	{
		Solution<d1> sol;
		sol.nodesCount = 51;
		//sol.nodesCount = ode.intCount + 1;
		sol.step = (ode.stopTime - ode.startTime) / (sol.nodesCount - 1);
		sol.points = new Point<d1>[sol.nodesCount];
		sol.isInfinit = false;
		sol.points[0] = ode.startPoint;
		sol.startTime = ode.startTime;
		sol.stopTime = ode.stopTime;

		double t = sol.startTime;
		double h = sol.step;
		Point<d1> k[4];
		for (int i = 0; i < sol.nodesCount - 1; i++)
		{
			k[0] = ode.fun(sol.points[i], t) * h;
			k[1] = ode.fun(sol.points[i] + k[0] * 0.5, t + 0.5 * h) * h;
			k[2] = ode.fun(sol.points[i] + k[1] * 0.5, t + 0.5 * h) * h;
			k[3] = ode.fun(sol.points[i] + k[2], t + h) * h;

			sol.points[i + 1] = sol.points[i] + (k[0] + k[1] * 2.0 + k[2] * 2.0 + k[3]) * (1.0 / 6.0);

			if (sol.points[i + 1].abs() > upperBound)
			{
				sol.isInfinit = true;
				sol.stopTime = t;
				sol.nodesCount = i;
				return sol;
			}
			t += h;
		}
		return sol;
	}
private:
	double upperBound;
};

#endif /* RKSOLVER_H_ */
