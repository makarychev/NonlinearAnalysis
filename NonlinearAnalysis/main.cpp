#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include "ResultFile.h"
#include "CorrelationDimension.h"
#include "PyPlot.h"

using namespace std;


// [1] - path to Runge-Kutta file result
// [2] - tau
int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		cout << "Please specify all parameters:" << endl;
		cout << "1) path to Runge-Kutta file result" << endl;
		cout << "2) tau" << endl;
		cout << "3) path to python file"<< endl;
		cout << "Example: \"C:\\result.txt\" 16" << endl;
		return 1;
	}
	if (argc > 3)
	{

	}
	using Matrix = boost::numeric::ublas::matrix < double > ;
	Matrix m(0, 0);
	Matlab::ResultFile::ReadMatrix(argv[1], 1, 3, m); 
	boost::numeric::ublas::matrix_row<Matrix> rowY(m, 1); // 0 - x; 1 - y; 2 - z
	// currently we have time series by y

	const size_t tau = std::stoi(argv[2]);
	auto _log = [](double a){ return log(a); }; // log10
	NonlinearMath::CorrelationDimension<double> objNonLinear;
	
	size_t nStep = 80;
	double epsilon = 0;
	double step = 0.01;
	vector<double> vEpsilon;
	for (size_t i = 0; i < nStep; i++)
	{
		epsilon += step;
		vEpsilon.push_back(_log(epsilon));
	}

	Python::PyPlot pyPlot;
	std::string m_sScriptsPath(argv[3]);
	pyPlot.Prepare(m_sScriptsPath);
	vector<double> vResult;
	
	for (size_t N = 13; N < 21; N++)
	{
		double epsilon	= 0;
		double step = 0.01;
		for (size_t i = 0; i < nStep; i++)
		{
			epsilon += step;
			double result = objNonLinear.Evaluate(rowY, tau, N, epsilon);
			//cout << _log(epsilon) << " | " << _log(result) / _log(epsilon) << endl;
			vResult.push_back(_log(result) / _log(epsilon));
		}
		pyPlot.Spline(vEpsilon, vResult);
		vResult.clear();
	}

	int i = 0;
	i++;
	pyPlot.Show();

	return 0;
}