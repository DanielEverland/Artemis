#pragma once

#include "Vector3Base.h"

namespace ArtemisEngine::Maths::Vectors
{
	struct DoubleVector3 : public Vector3Base<double>
	{
		using Vector3Base::Vector3Base;

		static const DoubleVector3 One;
		static const DoubleVector3 Zero;
		static const DoubleVector3 Up;
		static const DoubleVector3 Down;
		static const DoubleVector3 Right;
		static const DoubleVector3 Left;
		static const DoubleVector3 Forward;
		static const DoubleVector3 Back;
	};
}