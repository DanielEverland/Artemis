#pragma once

#if defined FLOAT_VECTOR
#include "Math/Vectors/FloatVector2.h"
#else
#include "Math/Vectors/DoubleVector2.h"
#endif

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
	typedef ArtemisEngine::Maths::Vectors::FloatVector2 Vector2;
#else
	typedef ArtemisEngine::Maths::Vectors::DoubleVector2 Vector2;	
#endif
}