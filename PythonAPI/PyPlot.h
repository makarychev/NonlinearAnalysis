#pragma once
#include "PythonExecutor.h"

#include <vector>

namespace Python {
	template <class T>
	std::string getArray(const std::vector<T>& vX)
	{
		std::string sAxis("np.array([");
		for (const auto &elem : vX)
		{
			sAxis += std::to_string(elem) + ",";
		}
		sAxis = sAxis.substr(0, sAxis.size() - 1);
		sAxis += "])";

		return sAxis;
	}

	class PyPlot
	{
	public:
		PyPlot();
		~PyPlot();

		int Prepare(std::string sScriptPath)
		{
			int retCode = 0;
			retCode = pyExecutor.ExecuteString("import matplotlib.pyplot as plt");
			retCode = pyExecutor.ExecuteString("import numpy as np");
			retCode = pyExecutor.ExecuteString("import sys");
			retCode = pyExecutor.ExecuteString("from scipy.interpolate import spline");
			std::string s0("sys.path.insert(0,\'" + sScriptPath + "\')");
			retCode = pyExecutor.ExecuteString(s0);
			retCode = pyExecutor.ExecuteString("import pyPlotTest");
			return retCode;
		}

		template <class T>
		int Spline(const std::vector<T>& vX, const std::vector<T>& vY)
		{
			std::string str1("axis_x = " + getArray<T>(vX));
			//cout << str1 << endl;
			pyExecutor.ExecuteString(str1);
			str1 = "axis_y = " + getArray<T>(vY);
			//cout << str1 << endl;
			pyExecutor.ExecuteString(str1);

			pyExecutor.ExecuteString("pyPlotTest.Plot2D(axis_x, axis_y)");

			return 0;
		}

		int Show()
		{
			return pyExecutor.ExecuteString("pyPlotTest.Show()");
		}
	private:
		PythonExecutor pyExecutor;
	};
}