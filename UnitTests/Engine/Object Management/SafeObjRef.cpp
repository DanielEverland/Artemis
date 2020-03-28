#include "pch.h"

#include "Source/Game/Object Management/SafeObjRef.h"
#include "Include/Game/SafePtr.h"

using namespace ArtemisEngine;

class TestClass
{
};

class BaseClass
{
};

class DerivedClass : public BaseClass
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
TEST(SafeObjRefTest, CompareSafePtr)
{
	SafeObjRef<TestClass>* a = new SafeObjRef<TestClass>(new TestClass());
	SafeObjRef<TestClass>* b = new SafeObjRef<TestClass>(new TestClass());

	SafePtr<TestClass> fromA = a->GetSafePtr();

	ExpectTrue((*a) == fromA);
	ExpectTrue(fromA == (*a));
	ExpectFalse((*b) == fromA);
	ExpectFalse(fromA == (*b));
}
TEST(SafeObjRefTest, CompareNotSafePtr)
{
	SafeObjRef<TestClass>* a = new SafeObjRef<TestClass>(new TestClass());
	SafeObjRef<TestClass>* b = new SafeObjRef<TestClass>(new TestClass());

	SafePtr<TestClass> fromA = a->GetSafePtr();
	
	ExpectTrue((*b) != fromA);
	ExpectTrue(fromA != (*b));
	ExpectFalse((*a) != fromA);
	ExpectFalse(fromA != (*a));
}
TEST(SafeObjRefTest, ConstructionDerivedClass)
{
	SafeObjRef<BaseClass>* objRef = new SafeObjRef<BaseClass>(new DerivedClass());

	SafePtr<BaseClass> basePtr = objRef->GetSafePtr();
	SafePtr<DerivedClass> derivedPtr = objRef->GetSafePtr();

	ExpectTrue(basePtr.IsValid());
	ExpectTrue(derivedPtr.IsValid());
}