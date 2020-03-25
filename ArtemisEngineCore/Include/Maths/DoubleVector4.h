#pragma once

#include "Vector4Base.h"

namespace ArtemisEngine::Maths::Vectors
{
	struct DoubleVector4 : public Vector4Base<double>
	{
		using Vector4Base::Vector4Base;
	};
}