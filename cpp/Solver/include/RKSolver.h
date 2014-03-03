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
	Point operator-(Point &p)
	{
		Point<dim>sub;
		for (int i = 0; i < dim; i++)
		{
			sub.X[i] = this->X[i] - p.X[i];
		}
		return sub;
	}


	double& operator[](int i)
	{
		return X[i];
	}

	const double operator[](int i) const
	{
		return X[i];
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
	//int intCount;
};


template <int dim>
class Solution
{
public:
	Solution(const Solution& s)
	{
		this->nodesCount = s.nodesCount;
		this->step = s.step;
		this->points = s.points;
		this->isInfinit = s.isInfinit;
		this->startTime = s.startTime;
		this->stopTime = s.stopTime;
		this->pCopyCounter = s.pCopyCounter;
		(*pCopyCounter)++;
	}

	~Solution()
	{
		(*pCopyCounter)--;
		if (*pCopyCounter == 0)
		{
			delete pCopyCounter;
			delete []points;
		}
	}

	const Point<dim>& operator[](int i)
	{
		return points[i];
	}

	const Point<dim>* GetData() const
	{
		return points;
	}

	int nodesCount;
	double step;
	Point<dim>* points;
	bool isInfinit;
	double startTime;
	double stopTime;
	int* pCopyCounter;
private:
	Solution()
	{
		pCopyCounter = new int;
		*pCopyCounter = 1;
	}

	Solution& operator=(const Solution& s)
	{
		return *this;
	}

	template <int d1>
	friend class Solver;
	template<int d>
	friend std::ostream& operator<<(std::ostream& stream, Solution<d> sol);
};

template <int d>
std::ostream &operator<<(std::ostream& stream, Solution<d> sol)
{
	for (int i = 0; i < sol.nodesCount; i++)
	{
		stream << sol.points[i] << std::endl;
	}
	return stream;
};

template <int d1>
class Solver
{
public:
	Solution<d1> Solve(Point<d1> (*ode)(Point<d1> p, double t), Point<d1> y0, double start, double end, double step)
	{
		Solution<d1> sol;
		return sol;
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
	double EffOrder(Ode<d1> ode)
	{
		int Nodes[3] = {128, 256, 512};
		Point<d1> S[3];
		Solution<d1> sol[3];
		for (int s = 0; s < 3; s++)
		{

			sol[s].nodesCount = Nodes[s];
			//sol.nodesCount = ode.intCount + 1;
			sol[s].step = (ode.stopTime - ode.startTime) / (sol[s].nodesCount - 1);
			sol[s].points = new Point<d1>[sol[s].nodesCount];
			sol[s].isInfinit = false;
			sol[s].points[0] = ode.startPoint;
			sol[s].startTime = ode.startTime;
			sol[s].stopTime = ode.stopTime;
			double t = sol[s].startTime;
			double h = sol[s].step;
			Point<d1> k[4];
			for (int i = 0; i < sol[s].nodesCount - 1; i++)
			{
				k[0] = ode.fun(sol[s].points[i], t) * h;
				k[1] = ode.fun(sol[s].points[i] + k[0] * 0.5, t + 0.5 * h) * h;
				k[2] = ode.fun(sol[s].points[i] + k[1] * 0.5, t + 0.5 * h) * h;
				k[3] = ode.fun(sol[s].points[i] + k[2], t + h) * h;
				sol[s].points[i + 1] = sol[s].points[i] + (k[0] + k[1] * 2.0 + k[2] * 2.0 + k[3]) * (1.0 / 6.0);
				t += h;
			}
			S[s] = sol[s][sol[s].nodesCount - 1];
			std::cout << S[s] << "\n";
			//sol.~Solution();
		}
		double order;
		Point<d1> P1, P2;
		P1 = S[2]-S[1];
		P2 = S[1]-S[0];
		order = log(P1.abs() / P2.abs()) / log(0.5);
		return order;
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
