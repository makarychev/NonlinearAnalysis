#pragma once
#include <boost/numeric/ublas/matrix.hpp>


namespace Matlab
{
	class ResultFile
	{
	public:
		ResultFile();
		~ResultFile();
		static void ReadMatrix(std::string sFilePath, unsigned int nSkippedHeader, unsigned int nColumnCount, boost::numeric::ublas::matrix<double> &m);
	};
}


