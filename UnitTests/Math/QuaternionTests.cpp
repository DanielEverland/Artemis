#include "pch.h"

#include "Engine/Math.h"
#include "Engine/Quaternion.h"
#include "..\Utility\Comparison\ComparisonUtility.h"
#include "..\Utility\Comparison\ComparisonUtilityQuaternions.h"
#include "..\Utility\Comparison\ComparisonUtilityVectors.h"

using ArtemisEngine::Quaternion;
using namespace ArtemisEngine::UnitTests::Comparisons;

TEST(Quaternions, Empty)
{
	Quaternion quaternion{};


	ExpectZero(quaternion.X);
	ExpectZero(quaternion.Y);
	ExpectZero(quaternion.Z);
	ExpectZero(quaternion.W);
}
TEST(Quaternions, EulerConversion)
{
	Vector3 input(-45, 45, 30);


	Quaternion quaternion(input.x, input.y, input.z);
	Vector3 euler = quaternion.GetEulerAngles();

	
	ExpectNear(input, euler);
}
TEST(Quaternions, Rotation)
{
	Quaternion startRotation(25, 45, 30);
	Quaternion appliedRotation(0, 10, 0);
	Vector3 expectedValue(25, 55, 30);

	Quaternion rotated = appliedRotation * startRotation;

	Vector3 actualValue = rotated.GetEulerAngles();

	ExpectNear(expectedValue, actualValue);
}