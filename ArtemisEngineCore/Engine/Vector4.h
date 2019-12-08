#pragma once

#if defined FLOAT_VECTOR
#include "Math/Vectors/FloatVector4.h"
#else
#include "Math/Vectors/DoubleVector4.h"
#endif

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
	typedef ArtemisEngine::Math::Vectors::FloatVector4 Vector4;
#else
	typedef ArtemisEngine::Math::Vectors::DoubleVector4 Vector4;
#endif
}