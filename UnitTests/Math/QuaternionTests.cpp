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
	Vector3 input(0.2, -0.1, 1.5);


	Quaternion quaternion(input.x, input.y, input.z);
	Vector3 euler = quaternion.GetEulerAngles();

	
	ExpectNear(input, euler);
}