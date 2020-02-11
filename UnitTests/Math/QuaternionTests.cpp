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


	TempExpectZero(quaternion.X);
	TempExpectZero(quaternion.Y);
	TempExpectZero(quaternion.Z);
	TempExpectZero(quaternion.W);
}
TEST(Quaternions, Identity)
{
	Quaternion expectedResult(0, 0, 0, 1);
	Quaternion actualResult = Quaternion::GetIdentity();

	
	QuaternionExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, FromEuler)
{
	Quaternion expectedResult(0.31635482569715384, -0.044176908151091668, 0.4903870041208746, 0.8108567143667782);


	Quaternion actualResult = Quaternion::FromEuler(-30.54632, 22.452345, 56.124545);

	
	QuaternionExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, FromEulerVector)
{
	Quaternion expectedResult(0.31635482569715384, -0.044176908151091668, 0.4903870041208746, 0.8108567143667782);


	Quaternion actualResult = Quaternion::FromEuler(Vector3(-30.54632, 22.452345, 56.124545));


	QuaternionExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, ToEuler)
{
	Vector3 expectedResult(-24.545299999999997, 56.463429999999988, 12.453409999999998);
	Quaternion quaternion(0.23630741822024112, -0.43918868728586835, 0.19333409991110806, 0.84492249754978199);

	
	Vector3 actualResult = quaternion.GetEuler();


	VectorExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, NorthPoleSingularity)
{
	Vector3 expectedResult(0, 90, 0);
	Quaternion quaternion = Quaternion::FromEuler(expectedResult);


	Vector3 actualResult = quaternion.GetEuler();


	VectorExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, SouthPoleSingularity)
{
	Vector3 expectedResult(0, -90, 0);
	Quaternion quaternion = Quaternion::FromEuler(expectedResult);


	Vector3 actualResult = quaternion.GetEuler();


	VectorExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, Multiplication)
{
	Quaternion expectedResult(-0.06562161125000002, -0.07686467689500001, 0.147448188084, 0.14009445794);
	Quaternion quaternionA(0.523451, -0.25324, 0.25435, 0.25345);
	Quaternion quaternionB(-0.15453, 0.235234, 0.125445, 0.12445);


	Quaternion actualResult = quaternionA * quaternionB;


	QuaternionExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, MultiplicationAssignment)
{
	Quaternion expectedResult(-0.06562161125000002, -0.07686467689500001, 0.147448188084, 0.14009445794);
	Quaternion actualResult(0.523451, -0.25324, 0.25435, 0.25345);
	Quaternion quaternionB(-0.15453, 0.235234, 0.125445, 0.12445);


	actualResult *= quaternionB;


	QuaternionExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, Equality)
{
	Quaternion a(0.4563, -3451.0453, Math::Pi, 1);
	Quaternion b(0.4563, -3451.0453, Math::Pi, 1);

	
	TempExpectTrue(a == b);
}
TEST(Quaternions, Addition)
{
	Quaternion expectedResult(0.0902, 0.4685, 0.08884, 0.00003);
	Quaternion quaternionA(0.4353, 0.1234, -0.3465, 0.23523);
	Quaternion quaternionB(-0.3451, 0.3451, 0.43534, -0.2352);


	Quaternion actualResult = quaternionA + quaternionB;


	QuaternionExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, AdditionAssignment)
{
	Quaternion expectedResult(0.0902, 0.4685, 0.08884, 0.00003);
	Quaternion actualResult(0.4353, 0.1234, -0.3465, 0.23523);
	Quaternion quaternionB(-0.3451, 0.3451, 0.43534, -0.2352);


	actualResult += quaternionB;


	QuaternionExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, Subtraction)
{
	Quaternion expectedResult(0.7804, -0.2217, -0.78184, 0.47043);
	Quaternion quaternionA(0.4353, 0.1234, -0.3465, 0.23523);
	Quaternion quaternionB(-0.3451, 0.3451, 0.43534, -0.2352);


	Quaternion actualResult = quaternionA - quaternionB;


	QuaternionExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, SubtractionAssignment)
{
	Quaternion expectedResult(0.7804, -0.2217, -0.78184, 0.47043);
	Quaternion actualResult(0.4353, 0.1234, -0.3465, 0.23523);
	Quaternion quaternionB(-0.3451, 0.3451, 0.43534, -0.2352);


	actualResult -= quaternionB;


	QuaternionExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, ScalarMultiplication)
{
	Quaternion expectedResult(0.7221174, -0.4569525, 0.28529730000000003, -0.2031783);
	Quaternion quaternion(0.5452, -0.345, 0.2154, -0.1534);
	double scalar = 1.3245;


	Quaternion actualResult = quaternion * scalar;


	ExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, ScalarMultiplicationEqual)
{
	Quaternion expectedResult(0.7221174, -0.4569525, 0.28529730000000003, -0.2031783);
	Quaternion actualResult(0.5452, -0.345, 0.2154, -0.1534);
	double scalar = 1.3245;


	actualResult *= scalar;


	ExpectNear(expectedResult, actualResult);
}
TEST(Quaternions, Normalized)
{
	Quaternion expectedResult(-0.19460036679210727, 0.18143409662252974, 0.9472480307716923, 0.1786995635873098);
	Quaternion quaternion(-0.1345, 0.1254, 0.6547, 0.12351);


	Quaternion actualResult = quaternion.GetNormalized();


	ExpectNear(expectedResult, actualResult);
}

TEST(Quaternions, Rotation)
{
	Vector3 expectedResult(31.670876291653691, -0.68343385195173312, 71.162023144994777);
	Vector3 point(76.32, -1.145, 15.54);
	Quaternion rotation = Quaternion::FromEuler(-24.5453, 56.46343, 12.45341);


	Vector3 actualResult = rotation * point;


	ExpectNear(expectedResult, actualResult);
}