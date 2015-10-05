#pragma once

namespace NonlinearMath
{
	namespace StepFunction
	{
		template <class T>
		int Heaviside(T value)
		{
			if (value < 0)
				return 0;
			else
				return 1;
		}
	}
}
