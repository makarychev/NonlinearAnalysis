#include "ResultFile.h"

//#include <stdio.h> 
//#include <stdlib.h>
//#include <math.h>

#include <string>
#include <fstream>
#include <iostream>

#include <boost/numeric/ublas/io.hpp>

using namespace Matlab;
using namespace std;

ResultFile::ResultFile()
{
}


ResultFile::~ResultFile()
{
}
//
void ResultFile::ReadMatrix(std::string sFilePath, unsigned int nSkippedHeader, unsigned int nColumnCount, boost::numeric::ublas::matrix<double>& m)
{
	ifstream file;
	file.open(sFilePath); // "..\external_files\results\output.txt"

	// skip header files 
	string sHeader;
	for (unsigned int i = 0; i < nSkippedHeader; i++)
		getline(file, sHeader);

	unsigned int valuesCount = 1000;
	m.resize(nColumnCount, valuesCount);

	unsigned int j = 0;
	while (!file.eof())
	{
		for (unsigned int i = 0; i < nColumnCount; i++)
		{
			file >> m(i, j);
		}
		j++;
		if (j == valuesCount)
		{
			m.resize(nColumnCount, j * 10);
			valuesCount = j * 10;
		}
	}
	m.resize(nColumnCount, j-1);
}
