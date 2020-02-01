#pragma once

namespace ArtemisEngine
{
	class Quaternion
	{
	public:
		Quaternion() = default;
		Quaternion(double xRotation, double yRotation, double zRotation);
		Quaternion(double x, double y, double z, double w);

		double X;
		double Y;
		double Z;
		double W;
		
		static Quaternion GetIdentity();

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