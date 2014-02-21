#include <iostream>
#include <cmath>


struct Point
{
	double x1;
	double x2;
};


Point f(Point a, double t)
{
	const double omega = 1.0;
	const double alpha = 0.0;
	Point b;
	b.x1 = a.x2;
	b.x2 = -(omega - alpha * cos(2 * t)) * a.x1 + pow(a.x1, 3.0);
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
	res.nodesCount = 1000;
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
	if (s.solution == 0) return;
	delete []s.solution;
	s.solution = 0;
}

int main()
{
	Point w;
	w.x1 = 0.5;
	w.x2 = 0.5;
	OdeResult a = Ode(0, M_PI, w);
	std::cout<<"Inf:"<<a.isInfinit<<std::endl;
	for (int i = 0; i < a.nodesCount; i++)
	{
		std::cout<<a.solution[i].x1<<std::endl;
	}
	DestroyOdeResult(a);
	return 0;
}
