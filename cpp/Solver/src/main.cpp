#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

#include "RKSolver.h"

using namespace RKSolver;

class Timer
{
public:
	Timer()
	{
		t = clock();
		std::cout<<"Start"<<std::endl;
	}
	~Timer()
	{
		std::cout<<"Done!"<<std::endl;
		std::cout<<"Elapsed time:"<< (double)(clock() - t) / CLOCKS_PER_SEC<<std::endl;
	}
private:
	clock_t t;
};

Point<1> function(Point<1> y, double t)
{
	return {5.0};
}

int main()
{
	Timer t;

	Ode<1> ode{function, {1}, 0.0, 2.0, 0.1};
	Solver<1> rk;
	Solution<1> solution = rk.Solve(ode);
	std::cout<<solution;
	return 0;
}
