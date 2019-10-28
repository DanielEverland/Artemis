#pragma once

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
#include "Math/Vectors/FloatVector4.h"

	typedef ArtemisEngine::Math::Vectors::FloatVector4 Vector4;
#else
#include "Math/Vectors/DoubleVector4.h"

	typedef ArtemisEngine::Math::Vectors::DoubleVector4 Vector4;
#endif
}