#pragma once

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
#include "Math/FloatVector4.h"

	typedef ArtemisEngine::Math::FloatVector4 Vector4;
#else
#include "Math/DoubleVector4.h"

	typedef ArtemisEngine::Math::DoubleVector4 Vector4;
#endif
}