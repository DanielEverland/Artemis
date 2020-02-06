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
TEST(Quaternions, FromEuler)
{
	Quaternion expectedResult(0.4015387309747489, -0.13779797639735092, 0.2820094531819598, 0.8603772623355381);


	Quaternion actualResult(-30, 22, 56);

	
	ExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, ToEuler)
{
	Vector3 expectedResult(-24, 56, 12);
	Quaternion quaternion(-0.006797587987017614, -0.13456870804627263, 0.475885694635716, 0.869124767368528);

	
	Vector3 actualResult = quaternion.GetEulerAngles();


	ExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, Rotation)
{
	/*Quaternion q(10, 35, 90);
	Quaternion r(0, 10, 0);

	Quaternion s = r * q;*/

	/*for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				q = Quaternion(arr[x], arr[y], arr[z]);
			}
		}
	}*/

	/*Quaternion appliedRotation(0.008649721, -0.00880202, 0.00880202, 0.9998851);
	Vector3 expectedValue(45, 60, 30);

	Quaternion rotated = appliedRotation * startRotation;

	Vector3 actualValue = rotated.GetEulerAngles();

	ExpectNear(expectedValue, actualValue);*/
}