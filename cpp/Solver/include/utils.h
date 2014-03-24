#ifndef UTILS_H_
#define UTILS_H_

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


#endif /* UTILS_H_ */