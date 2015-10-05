#include "Matlab.h"
#include <fstream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace std;

Matlab::Matlab()
{
}

Matlab::~Matlab()
{
}

void Matlab::ConvertToCpp(std::string sFileName, std::string sOutputFileName)
{
	std::ifstream file;
	file.open(sFileName);
	if (file.is_open() == false)
		return;
	size_t params = 0, count = 0;
	double dVal{};
	file >> params >> count;
	cout << "Num: " << params << " Count: " << count << endl;
	boost::numeric::ublas::matrix<double> inpMatrix(params, count);
	for (size_t i = 0; ((i < count) && (!file.eof())); i++)
	{
		for (size_t j = 0; ((j < params) && (!file.eof())); j++)
		{
			file >> dVal;
			inpMatrix(j, i) = dVal;
		}
	}
	file.close();
	std::ofstream fileOut;
	fileOut.open(sOutputFileName);
	fileOut << inpMatrix;
	fileOut.close();
}

void Matlab::RevertFromCpp(std::string sFileName)
{

}