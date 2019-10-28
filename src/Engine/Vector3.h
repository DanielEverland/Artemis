#pragma once

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
#include "Math/Vectors/FloatVector3.h"

	typedef ArtemisEngine::Math::Vectors::FloatVector3 Vector3;
#else
#include "Math/Vectors/DoubleVector3.h"

	typedef ArtemisEngine::Math::Vectors::DoubleVector3 Vector3;
#endif
}