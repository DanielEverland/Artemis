#pragma once

#include "Vector2Base.h"

namespace ArtemisEngine::Math::Vectors
{
	struct DoubleVector2 : public Vector2Base<double>
	{
		using Vector2Base::Vector2Base;
	};
}