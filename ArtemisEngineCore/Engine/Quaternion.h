#pragma once

#include "Engine/Vector3.h"

using ArtemisEngine::Vector3;

namespace ArtemisEngine
{
	// Quaternions represent rotations in an efficient manner without suffering from gimbal lock.
	// Rotations can be multiplied with each other, and points can be rotated by being multiplied with a quaternion.
	// Note that multiplying a point is not communitative. The quaternion must be the first operand.
	class Quaternion
	{
	public:
		Quaternion() = default;
		Quaternion(Vector3 rotation);
		Quaternion(double xRotation, double yRotation, double zRotation);
		Quaternion(double x, double y, double z, double w);

		double X;
		double Y;
		double Z;
		double W;
		
		// Quaternion with no rotation.
		// (0, 0, 0, 1)
		static Quaternion GetIdentity();
		
		// Returns a quaternion that moves along a unit sphere.
		// Keeps the same orientation, but its magnitude becomes 1.
		Quaternion GetNormalized() const;
		Vector3 GetEulerAngles() const;
		double Magnitude() const;

		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator-(const Quaternion& other) const;
		Quaternion operator*(const Quaternion& other) const;
		Quaternion operator*(double scalar) const;
		Vector3 operator*(const Vector3& point) const;

		void operator+=(const Quaternion& other);
		void operator-=(const Quaternion& other);
		void operator*=(const Quaternion& other);
		void operator*=(double scalar);
		bool operator==(const Quaternion& other) const;

	private:
		void FromEuler(double x, double y, double z);
	};
}