#include "PyPlot.h"

using namespace std;
using namespace Python;

PyPlot::PyPlot()
{
	pyExecutor.Init();
}

PyPlot::~PyPlot()
{
	pyExecutor.Deinit();
}