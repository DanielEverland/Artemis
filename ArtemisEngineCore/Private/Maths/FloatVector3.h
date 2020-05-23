#pragma once

#include "Vector3Base.h"

namespace ArtemisEngine::Maths::Vectors
{
	struct FloatVector3 : public Vector3Base<float>
	{
		using Vector3Base::Vector3Base;
	};
}