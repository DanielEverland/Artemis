#include "pch.h"

#include "Source/Game/Object Management/SafeObjRef.h"
#include "Include/Game/SafePtr.h"

using namespace ArtemisEngine;

class TestClass
{
};

TEST(SafeObjRefTest, ToSafePtr)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr();

	ExpectTrue(ptr.IsValid());
}
TEST(SafeObjRefTest, Destruction)
{
	SafeObjRef<TestClass>* objRef;

	objRef = new SafeObjRef<TestClass>(new TestClass());
	SafePtr<TestClass> ptr = objRef->GetSafePtr();

	delete objRef;

	ExpectTrue(ptr.IsValid() == false);
}
TEST(SafeObjRefTest, Move)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafeObjRef<TestClass> move(new TestClass());
	move = std::move(objRef);

	ExpectTrue(move.IsValid());
	ExpectTrue(move.GetSafePtr().IsValid());

	ExpectFalse(objRef.IsValid());
	ExpectThrow(objRef.GetSafePtr(), NullReferenceException);
	ExpectThrow(objRef.GetRaw(), NullReferenceException);
}