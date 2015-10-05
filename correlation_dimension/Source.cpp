#include <fstream>
#include <string>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

#include "RungeKutt.h"

using namespace std;


int CorrelationDimension()
{

	return 0;
}


const double a = 0.1;
const double b = 0.1;
const double c = 14;


//  Rossler system
//  dx/dt = -y -z
//  dy/dt = x + ay
//  dz/dt = b + z(x-c)
// chaotic atractor - a=0.2 b=0.2 c=5.7
//                    a=0.1 b=0.1 c=14
double yr_kacat1(Vector vars)
{
	double f = -vars[2] - vars[3]; // -y - z
	return f;
}

double yr_kacat2(Vector vars)
{
	double f = vars[1] + a*vars[2]; // x + ay
	return f;
}

double yr_kacat3(Vector vars)
{
	double f = b + vars[3] * (vars[1] - c); // b + z(x-c)
	return f;
}

void my_test()
{
	Func f1 = yr_kacat1;
	Func f2 = yr_kacat2;
	Func f3 = yr_kacat3;

	Func arrF[] = { f1, f2, f3 };
	std::vector<Func> arrFun(begin(arrF), end(arrF));

	double arrStartPoints[] = { 0.1, 0.1, 0.1 };
	Vector vecStartPoints(begin(arrStartPoints), end(arrStartPoints));

	boost::numeric::ublas::matrix<double> result;

	RungeKutt(arrFun, 0, 100, 1000, vecStartPoints, result);
}
