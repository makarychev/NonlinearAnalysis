#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include "StepFunction.h"
#include "Distance.h"

namespace NonlinearMath
{
	template <class T>
	using Matrix = boost::numeric::ublas::matrix<T>;
	template <class T>
	using Row = boost::numeric::ublas::matrix_row<T>;

	template <class T>
	class CorrelationDimension
	{
	public:
		CorrelationDimension() {}
		~CorrelationDimension() {}
		// m - number of variable at vector
		double Evaluate(const std::vector<T> row, const size_t tau = 16, const size_t pointsCount = 3, const double epsilon = 0.1);

	private:
		T m_obj;
	};

	template <class T>
	double CorrelationDimension<T>::Evaluate(const std::vector<T> row, const size_t tau, const size_t pointsCount, const double epsilon)
	{
		using namespace std;
		vector<deque<T>> delayVector;

		// create delay points vector from input row
		for (unsigned int i = 0; i < row.size() - tau*pointsCount; i++)
		{
			deque<T> newPoint;
			for (unsigned int j = 0; j < pointsCount; j++)
				newPoint.push_back(row[i + tau * j]);	//newPoint.push_back(row[j + tau * (j - i)]);
			delayVector.push_back(newPoint);
		}

		size_t Summ = 0;
		// calculate vector of results
		for (const auto &it1 : delayVector)
		{
			for (const auto &it2 : delayVector)
			{
				double delta = epsilon - Distance::Vectors(it1, it2);
				Summ += StepFunction::Heaviside(delta);
			}
		}
		size_t Npow2 = delayVector.size() * delayVector.size();
		return  (double)Summ / Npow2;
	}
}