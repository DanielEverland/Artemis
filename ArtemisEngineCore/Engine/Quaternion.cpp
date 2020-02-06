#include "Quaternion.h"
#include "Math.h"

using namespace ArtemisEngine;

Quaternion::Quaternion(Vector3 rotation)
{
	FromEuler(rotation.x, rotation.y, rotation.z);
}

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

Quaternion Quaternion::GetNormalized() const
{
	double magnitude = Magnitude();

	return Quaternion(
		X / magnitude,
		Y / magnitude,
		Z / magnitude,
		W / magnitude);
}

double Quaternion::Magnitude() const
{
	double x = Math::Squared(X);
	double y = Math::Squared(Y);
	double z = Math::Squared(Z);
	double w = Math::Squared(W);

	double sum = x + y + z + w;

	double magnitude = Math::SquareRoot(sum);

	return magnitude;
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
	                                                                                                                                                                                                                                  
	product.X = W * other.X + X * other.W + Y * other.Z - Z * other.Y;
	product.Y = W * other.Y + Y * other.W + Z * other.X - X * other.Z;
	product.Z = W * other.Z + Z * other.W + X * other.Y - Y * other.X;
	product.W = W * other.W - X * other.X - Y * other.Y - Z * other.Z;
	
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
	(*this) = (*this) * other;
}
void Quaternion::FromEuler(double x, double y, double z)
{
	x *= Math::DegToRad;
	y *= Math::DegToRad;
	z *= Math::DegToRad;

	// Abbreviations for the various angular functions
	double xCos = Math::Cos(x / 2);
	double xSin = Math::Sin(x / 2);
	double yCos = Math::Cos(y / 2);
	double ySin = Math::Sin(y / 2);
	double zCos = Math::Cos(z / 2);
	double zSin = Math::Sin(z / 2);

	/*X = ySin * xCos * zSin + yCos * xSin * zCos;
	Y = ySin * xCos * zCos - yCos * xSin * zSin;
	Z = yCos * xCos * zSin - ySin * xSin * zCos;
	W = yCos * xCos * zCos + ySin * xSin * zSin;*/

	X = xSin * ySin * zCos + xCos * yCos * zSin;
	Y = xSin * yCos * zCos + xCos * ySin * zSin;
	Z = xCos * ySin * zCos - xSin * yCos * zSin;
	W = xCos * yCos * zCos - xSin * ySin * zSin;
}
bool equals(double a, double b, double epsilon)
{
	return (Math::Absolute(a - b) < epsilon);
}
Vector3 Quaternion::GetEulerAngles() const
{
	Vector3 euler;

	//euler.x = Math::ArcTan2(2 * Y * W - 2 * X * Z, 1 - 2 * Math::Squared(Y) - 2 * Math::Squared(Z));
	euler.x = Math::ArcTan2(2 * Z * W - 2 * Y * X, 1 - 2 * Math::Squared(Z) - 2 * Math::Squared(X));

	euler.x *= Math::RadToDeg;
	euler.y *= Math::RadToDeg;
	euler.z *= Math::RadToDeg;

	//euler.x += 90;

	return euler;
}

//const static double PI_OVER_2 = M_PI * 0.5;
	//const static double EPSILON = 1e-10;
	//double sqW, sqX, sqY, sqZ;

	//// quick conversion to Euler angles to give tilt to user
	//sqW = W * W;
	//sqX = X * X;
	//sqY = Y * Y;
	//sqZ = Z * Z;

	//euler[1] = asin(2.0 * (W * Y - X * Z));
	//if (PI_OVER_2 - fabs(euler[1]) > EPSILON) {
	//	euler[2] = atan2(2.0 * (X * Y + W * Z),
	//		sqX - sqY - sqZ + sqW);
	//	euler[0] = atan2(2.0 * (W * X + Y * Z),
	//		sqW - sqX - sqY + sqZ);
	//}
	//else {
	//	// compute heading from local 'doWn' vector
	//	euler[2] = atan2(2 * Y * Z - 2 * X * W,
	//		2 * X * Z + 2 * Y * W);
	//	euler[0] = 0.0;

	//	// If facing doWn, reverse YaW
	//	if (euler[1] < 0)
	//		euler[2] = M_PI - euler[2];
	//}