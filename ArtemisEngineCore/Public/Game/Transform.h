#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"

namespace ArtemisEngine
{
	struct Transform
	{
	public:
		Transform();
		Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
		
		Vector3 Position;
		Quaternion Rotation;
		Vector3 Scale;

		static const Transform Identity;

		[[nodiscard]] Matrix GetWorldMatrix() const;
	};
}
