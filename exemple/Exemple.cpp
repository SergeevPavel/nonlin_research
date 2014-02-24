#include <iostream>
#include <stdarg.h>

template <int dim>
class A
{
public:
	A(...)
	{
		double val;
		va_list vl;
		va_start(vl,dim);
		for (int i = 0; i < dim; i++)
		{
			val = va_arg(vl,double);
			std::cout << val << std::endl;
		}
		va_end(vl);
	}
};

int main()
{
	A <3> obj(1.0, 2.0, 3.0);
	return 0;
}
