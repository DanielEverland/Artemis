#pragma once

#include <string>

#include "Engine/Vector3.h"
#include "Debugging/IDebugStringReturner.h"
#include <sstream>

using ArtemisEngine::Debugging::IDebugStringReturner;
using ArtemisEngine::Vector3;
using std::string;
using std::stringstream;

namespace ArtemisEngine
{
	// Quaternions represent rotations in an efficient manner without suffering from gimbal lock.
	// Rotations can be multiplied with each other, and points can be rotated by being multiplied with a quaternion.
	// Note that multiplying a point is not communitative. The quaternion must be the first operand.
	struct Quaternion : IDebugStringReturner
	{
	public:
		Quaternion() = default;
		Quaternion(double x, double y, double z, double w);

		double X;
		double Y;
		double Z;
		double W;
		
		// Quaternion with no rotation.
		// (0, 0, 0, 1)
		static Quaternion GetIdentity();

		// Constructs a quaternion using euler angles.
		static Quaternion FromEuler(const Vector3& eulerAngles);

		// Constructs a quaternion using euler angles.
		static Quaternion FromEuler(double xRotation, double yRotation, double zRotation);
		
		// Returns a quaternion that moves along a unit sphere.
		// Keeps the same orientation, but its magnitude becomes 1.
		Quaternion GetNormalized() const;

		// Returns the euler angles of the current rotation.
		Vector3 GetEuler() const;

		// Returns the length of this quaternion.
		double Magnitude() const;

		// Returns a string of the quaternion with the format (X, Y, Z, W)
		string ToString() const;

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
		inline static const string PositiveInfinityText = "PositiveInfinity";
		inline static const string NegativeInfinityText = "NegativeInfinity";
		inline static const string NaNText = "NaN";

		stringstream& FormatNumber(stringstream& stream, std::streamsize defaultPrecision, double value) const;
	};
}