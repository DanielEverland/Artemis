#pragma once

#include "Vector3Base.h"

namespace ArtemisEngine
{
	namespace Math
	{
		struct FloatVector3 : public Vector3Base<float>
		{
		public:
			FloatVector3(int x, int y);
			FloatVector3(int x, int y, int z);
		};
	}
}