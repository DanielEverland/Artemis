#pragma once

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
#include "Math/Vectors/FloatVector2.h"

	typedef ArtemisEngine::Math::Vectors::FloatVector2 Vector2;
#else
#include "Math/Vectors/DoubleVector2.h"

	typedef ArtemisEngine::Math::Vectors::DoubleVector2 Vector2;
#endif
}