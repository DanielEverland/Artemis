#pragma once

#include "Engine/Vector3.h"

using ArtemisEngine::Vector3;

namespace ArtemisEngine
{
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
		
		static Quaternion GetIdentity();
		
		Quaternion GetNormalized() const;
		Vector3 GetEulerAngles() const;
		double Magnitude() const;

		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator-(const Quaternion& other) const;
		Quaternion operator*(const Quaternion& other) const;
		void operator+=(const Quaternion& other);
		void operator-=(const Quaternion& other);
		void operator*=(const Quaternion& other);
		bool operator==(const Quaternion& other) const;

	private:
		void FromEuler(double x, double y, double z);
	};
}