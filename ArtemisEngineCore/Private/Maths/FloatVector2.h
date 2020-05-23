#pragma once

#include "Vector2Base.h"

namespace ArtemisEngine::Maths::Vectors
{
	struct FloatVector2 : public Vector2Base<float>
	{
		using Vector2Base::Vector2Base;
	};
}