#pragma once

#include "Vector3Base.h"

namespace ArtemisEngine::Maths::Vectors
{
	class DoubleVector3 : public Vector3Base<double>
	{
		using Vector3Base::Vector3Base;
	};
}