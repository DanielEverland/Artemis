#pragma once

#include "Vector2Base.h"

namespace ArtemisEngine::Maths::Vectors
{
	struct DoubleVector2 : public Vector2Base<double>
	{
		using Vector2Base::Vector2Base;
	};
}