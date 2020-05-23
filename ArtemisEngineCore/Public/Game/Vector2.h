#pragma once

#if defined FLOAT_VECTOR
#include "Include/Maths/FloatVector2.h"
#else
#include "Include/Maths/DoubleVector2.h"
#endif

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
	typedef ArtemisEngine::Maths::Vectors::FloatVector2 Vector2;
#else
	typedef ArtemisEngine::Maths::Vectors::DoubleVector2 Vector2;	
#endif
}