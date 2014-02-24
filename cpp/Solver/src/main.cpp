#include <iostream>
#include <fstream>
#include <ctime>

#include "RKSolver.h"

int main()
{
	/*
	std::cout<<"Start"<<std::endl;
	clock_t t = clock();
	Calc();
	std::cout<<"Done!"<<std::endl;
	std::cout<<"Elapsed time:"<< (double)(clock() - t) / CLOCKS_PER_SEC<<std::endl;
	*/
	Point<4> p({1.0, 2.0, 3.0, 4.0});
	std::cout<<p;
	return 0;
}
