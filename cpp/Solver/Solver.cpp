#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>


struct Point
{
	double x1;
	double x2;
};


Point f(Point a, double t)
{
	const double omega = 1;
	const double alpha = 0;
	const double A = +2;
	Point b;
	b.x1 = a.x2;
	b.x2 = -(omega - alpha * cos(2 * t)) * a.x1 + (1 + A * cos(2 * t)) * pow(a.x1, 3.0);
	return b;
}

struct OdeResult
{
	Point* solution;
	double step;
	int nodesCount;
	bool isInfinit;
	double tStart;
	double tStop;
};

OdeResult Ode(double tStart, double tStop, Point X0)
{
	const double UPPER_BOUND = 10000000000000;
	OdeResult res;
	res.nodesCount = 100;
	res.step = (tStop - tStart) / res.nodesCount;
	res.solution = new Point[res.nodesCount];
	res.isInfinit = false;
	res.solution[0] = X0;
	res.tStart = tStart;
	res.tStop = tStop;

	double t = tStart;
	Point k[4];
	Point w;
	for (int i = 0; i < res.nodesCount - 1; i++)
	{
		k[0] = f(res.solution[i], t);
		k[0].x1 *= res.step;
		k[0].x2 *= res.step;
		w.x1 = res.solution[i].x1 + k[0].x1 * 0.5;
		w.x2 = res.solution[i].x2 + k[0].x2 * 0.5;
		k[1] = f(w, t);
		k[1].x1 *= res.step;
		k[1].x2 *= res.step;
		w.x1 = res.solution[i].x1 + k[1].x1 * 0.5;
		w.x2 = res.solution[i].x2 + k[1].x2 * 0.5;
		k[2] = f(w, t);
		k[2].x1 *= res.step;
		k[2].x2 *= res.step;
		w.x1 = res.solution[i].x1 + k[2].x1;
		w.x2 = res.solution[i].x2 + k[2].x2;
		k[3] = f(w, t);
		k[3].x1 *= res.step;
		k[3].x2 *= res.step;
		res.solution[i + 1].x1 = res.solution[i].x1 + (1.0 / 6.0) *
				(k[0].x1 + 2 * k[1].x1 + 2 * k[2].x1 + k[3].x1);
		res.solution[i + 1].x2 = res.solution[i].x2 + (1.0 / 6.0) *
				(k[0].x2 + 2 * k[1].x2 + 2 * k[2].x2 + k[3].x2);
		if ((fabs(res.solution[i + 1].x1) > UPPER_BOUND) || (fabs(res.solution[i + 1].x2) > UPPER_BOUND))
		{
			res.isInfinit = true;
			res.tStop = t;
			return res;
		}
		t += res.step;
	}
	return res;
}

void DestroyOdeResult(OdeResult s)
{
	delete []s.solution;
}

char** CreatePlane(int n, int m)
{
	char** plane = new char*[m];
	for (int i = 0; i < m; i++)
	{
		plane[i] = new char[n];
	}
	return plane;
}

void DestroyPlane(char** p, int n, int m)
{
	for (int i = 0; i < m; i++)
	{
		delete []p[i];
	}
	delete []p;
}

void SaveInFile(char** plane, int n, int m)
{
	std::fstream output("output.txt", std::fstream::out);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			output<<(int)(plane[i][j])<<' ';
		}
		output<<std::endl;
	}
	output.close();
}

void Calc()
{
	const int N = 500; // lines count
	const int M = 1000; // columns count
	const double xmin = 0.0;
	const double xmax = 1.5;
	const double ymin = -6.0;
	const double ymax = 6.0;

	char** plane = CreatePlane(N, M);
	double xStep = (xmax - xmin) / N;
	double yStep = (ymax - ymin) / M;

	Point currentPoint;
	currentPoint.x1 = xmin;
	currentPoint.x2 = ymin;

	for (int i = 0; i < M; i++)
	{
		currentPoint.x1 = xmin;
		for (int j = 0; j < N; j++)
		{

			OdeResult r = Ode(0, 6*M_PI, currentPoint);
			currentPoint.x1 += xStep;
			if (r.isInfinit)
			{
				plane[i][j] = 0;
			}
			else
			{
				plane[i][j] = 1;
			}
			DestroyOdeResult(r);
		}
		currentPoint.x2 += yStep;
	}

	SaveInFile(plane, N, M);
	DestroyPlane(plane, N, M);
}

int main()
{
	std::cout<<"Start"<<std::endl;
	clock_t t = clock();
	Calc();
	std::cout<<"Done!"<<std::endl;
	std::cout<<"Elapsed time:"<< (double)(clock() - t) / CLOCKS_PER_SEC<<std::endl;
	return 0;
}
