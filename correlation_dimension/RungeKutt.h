#pragma once

#include <vector>
#include <functional>
#include <fstream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;

typedef unsigned int uint;
typedef std::vector<double> Vector;
typedef std::function<double(Vector)> Func;

enum RungeKutt_Res
{
	RungeKutt_Res_Ok = 0,
	RungeKutt_Res_BadInput = 100,
};


// http://www.codenet.ru/progr/alg/Runge-Kutt-Method/
// interpretation from Delphi
RungeKutt_Res RungeKutt(std::vector<Func> arrFun,
	double fStartPoint,
	double fEndPoint,
	unsigned int nStepNum,
	Vector vecInitVal,
	boost::numeric::ublas::matrix<double> &result)
{
	uint nEquationNum = 0; // число уравнений
	uint nInitialNum = 0; // число начальных условий
	double fPartitionStep = 0; // шаг разбиения
	Vector vecVars; // вектор переменных включая независимую
	Vector vecVars2, vecVars3, vecVars4; // значения перем. для 2-4 коэф.
	Vector vecK1, vecK2, vecK3, vecK4; // вектор 1-ыx коэффициентов в методе// вектор 2 коэффициентов в методе// вектор 3 коэффициентов в методе // вектор 4 коэффициентов в методе
	uint i = 0; // счетчик цикла по иттерациям
	uint j = 0; // индекс коэф.-тов метода
	uint k = 0; // счетчик прочих циклов

	nEquationNum = arrFun.size();
	nInitialNum = vecInitVal.size();
	if (nInitialNum != nEquationNum)
		return RungeKutt_Res_BadInput;

	fPartitionStep = (fEndPoint - fStartPoint) / nStepNum; // находим величину шага разбиений
	using namespace boost::numeric::ublas;
	matrix<double> m(nEquationNum + 1, nStepNum + 1); // задаем размер матрицы ответов с незав. перем.
	vecVars.resize(nEquationNum + 1);
	vecVars2.resize(nEquationNum + 1);
	vecVars3.resize(nEquationNum + 1);
	vecVars4.resize(nEquationNum + 1);
	vecK1.resize(nEquationNum);
	vecK2.resize(nEquationNum);
	vecK3.resize(nEquationNum);
	vecK4.resize(nEquationNum);

	// Начальные значения переменных:
	vecVars[0] = fStartPoint;
	for (k = 0; k <= nInitialNum - 1; k++)
		vecVars[k + 1] = vecInitVal[k];
	for (j = 0; j <= nEquationNum; j++) // первая точка результата 
		m(j, 0) = vecVars[j];
	for (i = 0; i <= nStepNum - 1; i++) // начало цикла иттераций
	{
		for (j = 0; j < nEquationNum; j++)
			vecK1[j] = arrFun[j](vecVars)*fPartitionStep; // 1-й коэфф.
		// Находим значения переменных для второго коэф.
		vecVars2[0] = vecVars[0] + fPartitionStep / 2;
		for (k = 1; k <= nEquationNum; k++)
			vecVars2[k] = vecVars[k] + vecK1[k - 1] / 2;
		for (j = 0; j < nEquationNum; j++)
			vecK2[j] = arrFun[j](vecVars2)*fPartitionStep; // 2-й коэф.
		// Находим значения переменных для третьго коэф.
		vecVars3[0] = vecVars[0] + fPartitionStep / 2;
		for (k = 1; k <= nEquationNum; k++)
			vecVars3[k] = vecVars[k] + vecK2[k - 1] / 2;
		for (j = 0; j <= nEquationNum - 1; j++)
			vecK3[j] = arrFun[j](vecVars3)*fPartitionStep; // 3 коэфф.
		// Находим значения переменных для 4 коэф.
		vecVars4[0] = vecVars[0] + fPartitionStep;
		for (k = 1; k <= nEquationNum; k++)
			vecVars4[k] = vecVars[k] + vecK3[k - 1];
		for (j = 0; j <= nEquationNum - 1; j++)
			vecK4[j] = arrFun[j](vecVars4)*fPartitionStep; // 4 коэфф.
		// Находим новые значения переменных включая независимую
		vecVars[0] = vecVars[0] + fPartitionStep;
		for (k = 1; k <= nEquationNum; k++)
		{
			//cout << "vecK1[" << k-1 << "] = " << vecK1[k-1] << endl;
			//cout << "vecK2[" << k-1 << "] = " << vecK2[k-1] << endl;
			//cout << "vecK3[" << k-1 << "] = " << vecK3[k-1] << endl;
			//cout << "vecK4[" << k-1 << "] = " << vecK4[k-1] << endl;
			//cout << "(vecK1[k-1]+2*(vecK2[k-1]+vecK3[k-1]+vecK4[k-1]) = "  << vecK1[k-1]+2*(vecK2[k-1]+vecK3[k-1]+vecK4[k-1]) << endl;
			//cout << "(1/6)* res = "  << ((double)1/6)*(vecK1[k-1]+2*(vecK2[k-1]+vecK3[k-1]+vecK4[k-1])) << endl;
			vecVars[k] = vecVars[k] + ((double)1 / 6)*(vecK1[k - 1] + 2 * (vecK2[k - 1] + vecK3[k - 1]) + vecK4[k - 1]);
		}
		// Результат  иттерации:
		for (j = 0; j <= nEquationNum; j++)
			m(j, i + 1) = vecVars[j];
	} // конец итераций

	std::ofstream file;
	file.open("result.txt");
	file << m;
	file.close();
	std::cout << m << std::endl;

	return RungeKutt_Res_Ok; // код ошибки 0 - нет ошибок
}
