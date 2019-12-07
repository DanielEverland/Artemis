#pragma once

#include "Vector4Base.h"

namespace ArtemisEngine::Math::Vectors
{
	struct DoubleVector4 : public Vector4Base<double>
	{
		using Vector4Base::Vector4Base;
	};
}