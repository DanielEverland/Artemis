#include "Quaternion.h"
#include "Math.h"

using namespace ArtemisEngine;

Quaternion::Quaternion(double xRotation, double yRotation, double zRotation)
{
	FromEuler(xRotation, yRotation, zRotation);
}

Quaternion::Quaternion(double x, double y, double z, double w)
{
	this->X = x;
	this->Y = y;
	this->Z = z;
	this->W = w;
}

Quaternion Quaternion::GetIdentity()
{
	return Quaternion(0, 0, 0, 1);
}

bool Quaternion::operator==(const Quaternion& other) const
{
	return
		this->X == other.X &&
		this->Y == other.Y &&
		this->Z == other.Z &&
		this->W == other.W;
}
Quaternion Quaternion::operator+(const Quaternion& other) const
{
	Quaternion sum{};

	sum.X = this->X + other.X;
	sum.Y = this->Y + other.Y;
	sum.Z = this->Z + other.Z;
	sum.W = this->W + other.W;

	return sum;
}
Quaternion Quaternion::operator-(const Quaternion& other) const
{
	Quaternion difference{};

	difference.X = this->X - other.X;
	difference.Y = this->Y - other.Y;
	difference.Z = this->Z - other.Z;
	difference.W = this->W - other.W;

	return difference;
}
Quaternion Quaternion::operator*(const Quaternion& other) const
{
	Quaternion product{};

	static_assert(true, "Not implemented");

	return product;
}
void Quaternion::operator+=(const Quaternion& other)
{
	this->X += other.X;
	this->Y += other.Y;
	this->Z += other.Z;
	this->W += other.W;
}
void Quaternion::operator-=(const Quaternion& other)
{
	this->X -= other.X;
	this->Y -= other.Y;
	this->Z -= other.Z;
	this->W -= other.W;
}
void Quaternion::operator*=(const Quaternion& other)
{
	(*this) += (*this) * other;
}
void Quaternion::FromEuler(double yaw, double pitch, double roll) // yaw (Z), pitch (Y), roll (X)
{
	/*yaw *= M_PI / 180.0;
	pitch *= M_PI / 180.0;
	roll *= M_PI / 180.0;*/

	// Abbreviations for the various angular functions
	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

	W = cy * cp * cr + sy * sp * sr;
	X = cy * cp * sr - sy * sp * cr;
	Y = sy * cp * sr + cy * sp * cr;
	Z = sy * cp * cr - cy * sp * sr;
}
Vector3 Quaternion::GetEulerAngles() const
{
	Vector3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (W * X + Y * Z);
	double cosr_cosp = 1 - 2 * (X * X + Y * Y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (W * Y - Z * X);
	if (std::abs(sinp) >= 1)
		angles.y = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	else
		angles.y = std::asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (W * Z + X * Y);
	double cosy_cosp = 1 - 2 * (Y * Y + Z * Z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	/*angles.x *= 180.0 / M_PI;
	angles.y *= 180.0 / M_PI;
	angles.z *= 180.0 / M_PI;*/

	return angles;
}