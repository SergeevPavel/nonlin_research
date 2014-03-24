
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