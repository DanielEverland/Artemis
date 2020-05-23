#pragma once

#if defined FLOAT_VECTOR
#include "Source/Maths/FloatVector4.h"
#else
#include "Source/Maths/DoubleVector4.h"
#endif

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
	typedef ArtemisEngine::Maths::Vectors::FloatVector4 Vector4;
#else
	typedef ArtemisEngine::Maths::Vectors::DoubleVector4 Vector4;
#endif
}