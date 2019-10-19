#pragma once

#include "Vector3Base.h"

namespace ArtemisEngine
{
	namespace Math
	{
		struct DoubleVector3 : public Vector3Base<double>
		{
		public:
			DoubleVector3(int x, int y);
			DoubleVector3(int x, int y, int z);
		};
	}
}