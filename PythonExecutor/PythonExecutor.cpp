#include "PythonExecutor.h"
#include "Python.h"

using namespace Python;

PythonExecutor::PythonExecutor()
{
}

PythonExecutor::~PythonExecutor()
{
	if (Py_IsInitialized())
		Deinit();
}

void PythonExecutor::Init()
{
	Py_Initialize();
}

void PythonExecutor::Deinit()
{
	Py_Finalize();
}

int PythonExecutor::ExecuteString(std::string sCommand)
{
	return PyRun_SimpleString(sCommand.c_str());
}
