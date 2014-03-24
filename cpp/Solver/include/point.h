#ifndef POINT_H_
#define POINT_H_

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

#endif /* POINT_H_ */