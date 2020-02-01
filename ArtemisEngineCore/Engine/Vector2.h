#pragma once

#if defined FLOAT_VECTOR
#include "Maths/Vectors/FloatVector2.h"
#else
#include "Maths/Vectors/DoubleVector2.h"
#endif

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
	typedef ArtemisEngine::Maths::Vectors::FloatVector2 Vector2;
#else
	typedef ArtemisEngine::Maths::Vectors::DoubleVector2 Vector2;	
#endif
}