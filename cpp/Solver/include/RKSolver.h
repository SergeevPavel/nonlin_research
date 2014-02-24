/*
 * RKSolver.h
 *
 *  Created on: 24.02.2014
 *      Author: pavel
 */

#ifndef RKSOLVER_H_
#define RKSOLVER_H_


#include <cstring>
#include <iostream>
#include <initializer_list>


template <int dim>
class Point
{
public:
	Point()
	{
		memset(X, 0x00, sizeof(double) * dim);
	}

	Point(double i_X[dim])
	{
		memcpy(X, i_X, sizeof(double) * dim);
	}

	Point(std::initializer_list<double> i_X)
	{
		memcpy(X, i_X.begin(), sizeof(double) * dim);
	}

	void Print()
	{
		for (int i = 0; i < dim; i++)
		{
			std::cout<<X[i]<<' ';
		}
		std::cout<<std::endl;
	}
	template<int d>
	friend std::ostream& operator<<(std::ostream& stream, Point<d> P);
private:
	double X[dim];
};

template <int d>
std::ostream &operator<<(std::ostream& stream, Point<d> P)
{
	for (int i = 0; i < d; i++)
	{
		std::cout<<P.X[i]<<' ';
	}
	std::cout<<std::endl;
	return stream;
}

//void Calc();

#endif /* RKSOLVER_H_ */
