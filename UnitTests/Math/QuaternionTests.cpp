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


	ExpectNear(expectedResult, actualResult);
}

TEST(Quaternions, Addition)
{
	Quaternion expectedResult(0.0902, 0.4685, 0.08884000000000003, 0.000030000000000002247);
	Quaternion quaternionA(0.4353, 0.1234, -0.3465, 0.23523);
	Quaternion quaternionB(-0.3451, 0.3451, 0.43534, -0.2352);


	Quaternion actualResult = quaternionA + quaternionB;


	ExpectNear(expectedResult, actualResult);
}

TEST(Quaternions, ScalarMultiplication)
{
	Quaternion expectedResult(0.7221174, -0.4569525, 0.28529730000000003, -0.2031783);
	Quaternion quaternion(0.5452, -0.345, 0.2154, -0.1534);
	double scalar = 1.3245;


	Quaternion actualResult = quaternion * scalar;


	ExpectNear(expectedResult, actualResult);
}

TEST(Quaternions, Normalized)
{
	Quaternion expectedResult(-0.19460036679210727, 0.18143409662252974, 0.9472480307716923, 0.1786995635873098);
	Quaternion quaternion(-0.1345, 0.1254, 0.6547, 0.12351);


	Quaternion actualResult = quaternion.GetNormalized();


	ExpectNear(expectedResult, actualResult);
}

TEST(Quaternions, Conjugate)
{
	Quaternion expectedResult(-0.4351, 0.4745, -0.1543, 0.7563);
	Quaternion quaternion(0.4351, -0.4745, 0.1543, 0.7563);


	Quaternion actualResult = quaternion.GetConjugate();


	ExpectNear(expectedResult, actualResult);
}

TEST(Quaternions, Rotation)
{
	Vector3 expectedResult(0, 1, 0);
	Vector3 point(1, 0, 0);
	Quaternion rotation(0, 90, 0);


	Vector3 actualResult = rotation * point;


	ExpectNear(expectedResult, actualResult);
}