#pragma once

#include "Vector4Base.h"

namespace ArtemisEngine::Maths::Vectors
{
	struct FloatVector4 : public Vector4Base<float>
	{
		using Vector4Base::Vector4Base;
	};
}