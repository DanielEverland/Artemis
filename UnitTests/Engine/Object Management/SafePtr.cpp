#include "pch.h"

#include "Engine/Object Management/SafeObjRef.h"
#include "Engine/SafePtr.h"

using namespace ArtemisEngine;

class TestClass
{
public:
	int value = 5;
};

TEST(SafePtrTest, Construction)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr();

	ExpectTrue(ptr.IsValid());
}
TEST(SafePtrTest, Dereferencing)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr();

	ExpectEqual(5, ptr->value);
}
TEST(SafePtrTest, RawPointer)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr();

	TestClass* rawPtr = ptr;

	ExpectTrue(rawPtr != nullptr);
}
TEST(SafePtrTest, BoolConversion)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr();

	ExpectTrue(bool(ptr));
}