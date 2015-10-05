#pragma once


#define DEFAULT_STEPS 1000

int test();
unsigned short rk(double (*rightParts[])(double,double[]),
				  const double initConds[], unsigned int count, double first, double last,
				  double unDependVarPoints[], double *dependVarsRes[],
				  unsigned int steps = DEFAULT_STEPS);