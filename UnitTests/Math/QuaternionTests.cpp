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
	Quaternion expectedResult(0.39987815192716875, -0.139654925870582, 0.2872776995099842, 0.8591073790019765);


	Quaternion actualResult(-30.54632, 22.452345, 56.124545);

	
	ExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, ToEuler)
{
	Vector3 expectedResult(-24.5453, 56.46343, 12.45341);
	Quaternion quaternion(-0.0065813969517179716, -0.136038364086436, 0.47981398733518227, 0.866734553521644);

	
	Vector3 actualResult = quaternion.GetEulerAngles();


	ExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, Multiplication)
{
	Quaternion expectedResult(-0.06562161125000002, -0.07686467689500001, 0.147448188084, 0.14009445794);
	Quaternion quaternionA(0.523451, -0.25324, 0.25435, 0.25345);
	Quaternion quaternionB(-0.15453, 0.235234, 0.125445, 0.12445);

	Quaternion actualResult = quaternionA * quaternionB;

	ExpectEqual(expectedResult, actualResult);
}