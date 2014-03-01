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

namespace RKSolver
{

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

	Point operator+(const Point& p) const
	{
		Point<dim>sum;
		for (int i = 0; i < dim; i++)
		{
			sum.X[i] = this->X[i] + p.X[i];
		}
		return sum;
	}

	Point operator+(double add) const
	{
		Point<dim>sum;
		for (int i = 0; i < dim; i++)
		{
			sum.X[i] = this->X[i] + add;
		}
		return sum;
	}

	Point& operator+=(const Point& p)
	{
		for (int i = 0; i < dim; i++)
		{
			this->X[i] += p.X[i];
		}
		return *this;
	}

	Point& operator+=(double add)
	{
		for (int i = 0; i < dim; i++)
		{
			this->X[i] += add;
		}
		return *this;
	}

	Point operator*(double mul) const
	{
		Point<dim>res;
		for (int i = 0; i < dim; i++)
		{
			res.X[i] = this->X[i] * mul;
		}
		return res;
	}

	Point& operator*=(double mult)
	{
		for (int i = 0; i < dim; i++)
		{
			this->X[i] *= mult;
		}
		return *this;
	}


	double& operator[](const int ind)
	{
		return X[ind];
	}

	double abs()
	{
		double sum;
		for (int i = 0; i < dim; i++)
		{
			sum += X[i] * X[i];
		}
		return sqrt(sum);
	}

	template<int d>
	friend std::ostream& operator<<(std::ostream& stream, Point<d> P);
private:
	double X[dim];
};

template <int d>
std::ostream &operator<<(std::ostream& stream, Point<d> p)
{
	for (int i = 0; i < d; i++)
	{
		stream<<p.X[i]<<' ';
	}
	return stream;
};

template <int dim>
class Ode
{
public:
	Point<dim> (*fun)(Point<dim> p, double t);
	Point<dim> startPoint;
	double startTime;
	double stopTime;
	double prec;
};


template <int dim>
class Solution
{
public:
	~Solution()
	{
		//delete []points;
		std::cout<<"destructor"<<std::endl;
	}
private:
	Solution()
	{

	}
	template <int d1>
	friend class Solver;
	template<int d>
	friend std::ostream& operator<<(std::ostream& stream, Solution<d> sol);

	int nodesCount;
	double step;
	Point<dim>* points;
	bool isInfinit;
	double startTime;
	double stopTime;
};

template <int d>
std::ostream &operator<<(std::ostream& stream, Solution<d> sol)
{
	for (int i = 0; i < sol.nodesCount; i++)
	{
		stream<<sol.points[i]<<std::endl;
	}
	return stream;
};

template <int d1>
class Solver
{
public:
	Solution<d1> Solve(Ode<d1> ode)
	{
		Solution<d1> sol{};
		sol.nodesCount = 10;
		sol.step = (ode.stopTime - ode.startTime) / sol.nodesCount;
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

			if (sol.points[i + 1].abs() > UPPER_BOUND)
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
	const double UPPER_BOUND = 10000000000000.0;
};

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

}
#endif /* RKSOLVER_H_ */
