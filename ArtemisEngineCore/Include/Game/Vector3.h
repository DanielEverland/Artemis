#pragma once

#if defined FLOAT_VECTOR
#include "Include/Maths/FloatVector3.h"
#else
#include "Include/Maths/DoubleVector3.h"
#endif

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
	typedef ArtemisEngine::Maths::Vectors::FloatVector3 Vector3;
#else
	typedef ArtemisEngine::Maths::Vectors::DoubleVector3 Vector3;
#endif
}