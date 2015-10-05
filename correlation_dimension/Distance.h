#pragma once

namespace NonlinearMath
{
	namespace Distance
	{
		template <class T>
		double Vectors(const std::deque<T > &point1, const std::deque<T> &point2)
		{
			// sqrt(sqr(x2-x1) + sqr(y2-y1) + ...)
			double distance = 0;
			for (auto it1 = begin(point1), it2 = begin(point2); it1 != end(point1), it2 != end(point2); ++it1, ++it2)
			{
				distance += pow((*it1 - *it2), 2); // some trouble with list
			}
			return sqrt(distance);
		}

		template <class T>
		double Max(const std::vector<std::deque<T>> &delayVector)
		{
			auto comparator = [](auto a, auto &b){if (a > b) b = a; }
			return MinMax(delayVector, comparator);
		}

		template <class T>
		double Min(const std::vector<std::deque<T>> &delayVector)
		{
			auto comparator = [](auto a, auto &b){if (a < b) b = a; }
			return MinMax(delayVector, comparator);
		}

		template <class T, class Comparator>
		double MinMax(const std::vector<std::deque<T>> &delayVector, Comparator _FuncComparator)
		{
			using namespace std;
			double result = 0;
			for (int i = 0; i < delayVector.size(); i++)
			{
				for (int j = i + 1; j < delayVector.size(); j++)
				{
					double distance = Distance::Vectors<T>(delayVector[i], delayVector[j]);
					if (_FuncComparator(distance, result))
						result = distance;
				}
			}
			return result;

		}
	}
}