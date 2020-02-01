#pragma once

#if defined FLOAT_VECTOR
#include "Math/Vectors/FloatVector3.h"
#else
#include "Math/Vectors/DoubleVector3.h"
#endif

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
	typedef ArtemisEngine::Maths::Vectors::FloatVector3 Vector3;
#else
	typedef ArtemisEngine::Maths::Vectors::DoubleVector3 Vector3;
#endif
}