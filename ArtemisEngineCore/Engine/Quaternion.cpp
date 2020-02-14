#include "Quaternion.h"
#include "Math.h"

using namespace ArtemisEngine;

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
	double x = Math::Square(X);
	double y = Math::Square(Y);
	double z = Math::Square(Z);
	double w = Math::Square(W);

	double sum = x + y + z + w;

	double magnitude = Math::SquareRoot(sum);

	return magnitude;
}
Quaternion Quaternion::FromEuler(const Vector3& eulerAngles)
{
	return FromEuler(eulerAngles.X, eulerAngles.Y, eulerAngles.Z);
}
Quaternion Quaternion::FromEuler(double xRotation, double yRotation, double zRotation)
{
	xRotation = Math::DegreesToRadians(xRotation);
	yRotation = Math::DegreesToRadians(yRotation);
	zRotation = Math::DegreesToRadians(zRotation);

	// Abbreviations for the various angular functions
	double xCos = Math::Cos(xRotation / 2);
	double xSin = Math::Sin(xRotation / 2);
	double yCos = Math::Cos(yRotation / 2);
	double ySin = Math::Sin(yRotation / 2);
	double zCos = Math::Cos(zRotation / 2);
	double zSin = Math::Sin(zRotation / 2);

	return Quaternion(
	 xCos * ySin * zSin - xSin * yCos * zCos,
	-xCos * ySin * zCos - xSin * yCos * zSin,
	 xCos * yCos * zSin - xSin * ySin * zCos,
	 xCos * yCos * zCos + xSin * ySin * zSin);
}
Vector3 Quaternion::GetEuler() const
{
	Vector3 euler;
	const double SingularityThreshold = 0.4999995;
	const double RadToDeg = 180.0 / Math::Pi;

	const double SingularityTest = Z * X - W * Y;

	const double YawY = 2.0 * (W * Z + X * Y);
	const double YawX = 1.0 - 2.0 * (Math::Square(Y) + Math::Square(Z));
	
	if (SingularityTest < -SingularityThreshold)
	{
		euler.X = Math::NormalizeAngle(-euler.Z - (2.0 * Math::ArcTan2(X, W) * RadToDeg));
		euler.Y = -90;
		euler.Z = 0;
	}
	else if (SingularityTest > SingularityThreshold)
	{
		euler.X = Math::NormalizeAngle(euler.Z - (2.0 * Math::ArcTan2(X, W) * RadToDeg));
		euler.Y = 90;
		euler.Z = 0;
	}
	else
	{
		euler.X = Math::ArcTan2(-2.0 * (W * X + Y * Z), 1.0 - 2.0 * (Math::Square(X) + Math::Square(Y))) * RadToDeg;
		euler.Y = Math::ArcSin(2.0 * SingularityTest) * RadToDeg;
		euler.Z = Math::ArcTan2(YawY, YawX) * RadToDeg;
	}

	return euler;
}

string ArtemisEngine::Quaternion::ToString() const
{
	std::stringstream stream;
	std::streamsize defaultPrecision = stream.precision();

	stream << "(";
	FormatNumber(stream, defaultPrecision, X) << ", ";
	FormatNumber(stream, defaultPrecision, Y) << ", ";
	FormatNumber(stream, defaultPrecision, Z) << ", ";
	FormatNumber(stream, defaultPrecision, W);
	stream << ")";

	return stream.str();
}
stringstream& Quaternion::FormatNumber(stringstream& stream, std::streamsize defaultPrecision, double value) const
{
	if (Math::IsPositiveInfinity(value))
	{
		stream << PositiveInfinityText;
	}
	else if (Math::IsNegativeInfinity(value))
	{
		stream << NegativeInfinityText;
	}
	else if (Math::IsNaN(value))
	{
		stream << NaNText;
	}
	else if (Math::IsFloatingPointIntegral(value))
	{
		stream << std::fixed << std::setprecision(1) << value;
	}
	else
	{
		stream << std::defaultfloat << std::setprecision(defaultPrecision) << value;
	}

	return stream;
}

Vector3 Quaternion::operator*(const Vector3& point) const
{
	double x = X * 2;
	double y = Y * 2;
	double z = Z * 2;
	double xx = X * x;
	double yy = Y * y;
	double zz = Z * z;
	double xy = X * y;
	double xz = X * z;
	double yz = Y * z;
	double wx = W * x;
	double wy = W * y;
	double wz = W * z;

	Vector3 res;
	res.X = (1.0 - (yy + zz)) * point.X + (xy - wz) * point.Y + (xz + wy) * point.Z;
	res.Y = (xy + wz) * point.X + (1.0 - (xx + zz)) * point.Y + (yz - wx) * point.Z;
	res.Z = (xz - wy) * point.X + (yz + wx) * point.Y + (1.0 - (xx + yy)) * point.Z;
	return res;
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

	
	                                                                                                                                                                                                                                  
	product.X = X * other.W + Y * other.Z - Z * other.Y + W * other.X;
	product.Y = -X * other.Z + Y * other.W + Z * other.X + W * other.Y;
	product.Z = X * other.Y - Y * other.X + Z * other.W + W * other.Z;
	product.W = -X * other.X - Y * other.Y - Z * other.Z + W * other.W;
	
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
Quaternion Quaternion::operator*(double scalar) const
{
	return Quaternion(
		this->X * scalar,
		this->Y * scalar,
		this->Z * scalar,
		this->W * scalar);
}
void Quaternion::operator*=(double scalar)
{
	this->X *= scalar;
	this->Y *= scalar;
	this->Z *= scalar;
	this->W *= scalar;
}