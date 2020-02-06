#include "pch.h"

#include <quaternion.h>

#include "Engine/Math.h"
#include "Engine/Quaternion.h"
#include "..\Utility\Comparison\ComparisonUtility.h"
#include "..\Utility\Comparison\ComparisonUtilityQuaternions.h"
#include "..\Utility\Comparison\ComparisonUtilityVectors.h"

using ArtemisEngine::Quaternion;
using irr::core::quaternion;
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
	double arr[3] = { -30, 25, 125 };

	double x = 0.0687661;
	double y = 0.3206688;
	double z = 0.862344;
	double w = 0.3857534;

	Quaternion q{};

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				q = Quaternion(arr[x], arr[y], arr[z]);
			}
		}
	}

	/*Quaternion appliedRotation(0.008649721, -0.00880202, 0.00880202, 0.9998851);
	Vector3 expectedValue(45, 60, 30);

	Quaternion rotated = appliedRotation * startRotation;

	Vector3 actualValue = rotated.GetEulerAngles();

	ExpectNear(expectedValue, actualValue);*/
}