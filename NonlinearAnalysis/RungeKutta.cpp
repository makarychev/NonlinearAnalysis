#include "RungeKutta.h"

#include <iostream>

using namespace std;


unsigned short rk(double (*rightParts[])(double,double[]),
				  const double initConds[], unsigned int count, double first, double last,
				  double unDependVarPoints[], double *dependVarsRes[],
				  unsigned int steps)
{

	if (last < first) return 2000;
	if (!steps) return 3000;
	if (!count) return 4000;

	unsigned int i, j, points = steps + 1;

	try{
		for(j = 0; j < count; ++j)
			dependVarsRes[j] = new double [points]; //get memory
	}
	catch(...){return 1000;}

	try{

		double tVar, delt = (last - first)/steps;
		
		double **xVars = new double*[4];
		for (int i = 0; i < 4; ++i)
			xVars[i] = new double[count];
		double **c = new double*[4];
		for (int i = 0; i < 4; ++i)
			c[i] = new double[count];

		// Initial values of vars and first point of results:
		for(j = 0; j < count; ++j){
			xVars[0][j] = initConds[j];
			dependVarsRes[j][0] = xVars[0][j];
		}
		tVar = first;
		unDependVarPoints[0] = tVar;

		for(i = 0; i < steps; ++i){
			// itterations begin
			for (j = 0; j < count; ++j){
				c[0][j] = rightParts[j](tVar, xVars[0])*delt;
				// Get values of vars for c[1]:
				xVars[1][j] = xVars[0][j] + c[0][j]/2.0;
			}
			tVar += delt/2.0;
			for (j = 0; j < count; ++j){
				c[1][j] = rightParts[j](tVar, xVars[1])*delt;
				// Get values of vars for c[2]:
				xVars[2][j] = xVars[0][j] + c[1][j]/2.0;
			}
			for (j = 0; j < count; ++j){
				c[2][j] = rightParts[j](tVar, xVars[2])*delt;
				// Get values of vars for c[3]:
				xVars[3][j] = xVars[0][j] + c[2][j];
			}
			tVar += delt/2.0;
			for (j = 0; j < count; ++j){
				c[3][j] = rightParts[j](tVar, xVars[3])*delt;
				// Get new values of vars (and Itteration result):
				dependVarsRes[j][i+1] = xVars[0][j] +=
					(c[0][j] + 2.0*(c[1][j] + c[2][j]) + c[3][j])/6.0;
			}
			unDependVarPoints[i+1] = tVar;
		} // Itterations end

	}//try

	catch(...){return 5000;} //а очищать память будет вызывающая программа

	return 0;//ok
}



double f0(double t, double x[]){
	return 2*t;
}

double f1(double t, double x[]){
	return 3*x[0];
}

int test()
{
	const unsigned int num = 2;
	unsigned int st, points, dst;
	double (*fun[])(double,double[]) = {f0,f1};
	double iC[] = {0.0,0.0};
	double t0 = 0.0, te = 10.0;
	double *dVP[num];

rep:

	cout << "Enter number of steps (min 10)\n";
	cin >> st;
	if (st < 10) goto rep;
	dst = st/10;

	points = st + 1;
	double *uDVP; 
	try{uDVP = new double [points];}
	catch(...) {cout << "Error: array is too big...\n" << endl; return -1;}

	unsigned short erc = rk(fun,iC,num,t0,te,uDVP,dVP,st);
	if (!erc){
		cout << "Returned with no errors\n\n ";
		for(unsigned int i = 0; i < points; i += dst){
			cout << uDVP << '\t' << dVP[0] << '\t' << dVP[1] << endl;
		}
	}
	else cout << "Returned code is " << erc << endl;

	delete [] uDVP;
	for(unsigned int i = 0; i < num; ++i) delete[] dVP; //free memory

	char ch;
	cout << "\nRepiat? [1/0]\n";
	cin >> ch;

	if (ch == '1') goto rep;

	return 0;
}