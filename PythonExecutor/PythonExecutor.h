#pragma once
#include <string>

namespace Python {
	class PythonExecutor
	{
	public:
		PythonExecutor();
		~PythonExecutor();
		void Init();
		void Deinit();
		int ExecuteString(std::string sCommand);
	private:

	};
}