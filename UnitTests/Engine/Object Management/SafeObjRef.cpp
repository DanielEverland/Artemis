#include "pch.h"

#include "Private/Game/Object Management/SafeObjRef.h"
#include "Public/Game/SafePtr.h"

using namespace ArtemisEngine;

class TestClass
{
};

class BaseClass
{
public:
	virtual void Test() { }
};

class DerivedClass : public BaseClass
{
};

TEST(SafeObjRefTest, ToSafePtr)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr<TestClass>();

	ExpectTrue(ptr.IsValid());
}
TEST(SafeObjRefTest, Destruction)
{
	SafeObjRef<TestClass>* objRef;

	objRef = new SafeObjRef<TestClass>(new TestClass());
	SafePtr<TestClass> ptr = objRef->GetSafePtr<TestClass>();

	delete objRef;

	ExpectTrue(ptr.IsValid() == false);
}
TEST(SafeObjRefTest, Move)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafeObjRef<TestClass> move(new TestClass());
	move = std::move(objRef);

	ExpectTrue(move.IsValid());
	ExpectTrue(move.GetSafePtr<TestClass>().IsValid());

	ExpectFalse(objRef.IsValid());
	ExpectThrow(objRef.GetSafePtr<TestClass>(), NullReferenceException);
	ExpectThrow(objRef.GetRaw(), NullReferenceException);
}
TEST(SafeObjRefTest, CompareSafePtr)
{
	SafeObjRef<TestClass>* a = new SafeObjRef<TestClass>(new TestClass());
	SafeObjRef<TestClass>* b = new SafeObjRef<TestClass>(new TestClass());

	SafePtr<TestClass> fromA = a->GetSafePtr<TestClass>();

	ExpectTrue((*a) == fromA);
	ExpectTrue(fromA == (*a));
	ExpectFalse((*b) == fromA);
	ExpectFalse(fromA == (*b));
}
TEST(SafeObjRefTest, CompareNotSafePtr)
{
	SafeObjRef<TestClass>* a = new SafeObjRef<TestClass>(new TestClass());
	SafeObjRef<TestClass>* b = new SafeObjRef<TestClass>(new TestClass());

	SafePtr<TestClass> fromA = a->GetSafePtr<TestClass>();
	
	ExpectTrue((*b) != fromA);
	ExpectTrue(fromA != (*b));
	ExpectFalse((*a) != fromA);
	ExpectFalse(fromA != (*a));
}
TEST(SafeObjRefTest, ConstructionDerivedClass)
{
	SafeObjRef<BaseClass>* objRef = new SafeObjRef<BaseClass>(new DerivedClass());

	SafePtr<BaseClass> basePtr = objRef->GetSafePtr<BaseClass>();
	SafePtr<DerivedClass> derivedPtr = objRef->GetSafePtr<DerivedClass>();

	ExpectTrue(basePtr.IsValid());
	ExpectTrue(derivedPtr.IsValid());
}