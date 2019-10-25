#pragma once

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
#include "Math/FloatVector2.h"

	typedef ArtemisEngine::Math::FloatVector2 Vector2;
#else
#include "Math/DoubleVector2.h"

	typedef ArtemisEngine::Math::DoubleVector2 Vector2;
#endif
}