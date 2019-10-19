#pragma once

namespace ArtemisEngine
{
#if defined FLOAT_VECTOR
#include "Math/FloatVector3.h"

	typedef ArtemisEngine::Math::FloatVector3 Vector3;
#else
#include "Math/DoubleVector3.h"

	typedef ArtemisEngine::Math::DoubleVector3 Vector3;
#endif
}