#include "pch.h"

#include "Include/Exceptions/NullReferenceException.h"
#include "Include/Game/SafePtr.h"

#include "Source/Game/Object Management/SafeObjRef.h"

using namespace ArtemisEngine;

class TestClass
{
public:
	int value = 5;
};

class Base
{
public:
	virtual void Test() { }
};
class Derived : public Base
{
};
class NotDerived
{
public:
	virtual void Test() { }
};

TEST(SafePtrTest, Construction)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr<TestClass>();

	ExpectTrue(ptr.IsValid());
}
TEST(SafePtrTest, Dereferencing)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr<TestClass>();

	ExpectEqual(5, ptr->value);
}
TEST(SafePtrTest, RawPointer)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr<TestClass>();

	TestClass* rawPtr = ptr;

	ExpectTrue(rawPtr != nullptr);
}
TEST(SafePtrTest, BoolConversion)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr<TestClass>();

	ExpectTrue(bool(ptr));
}
TEST(SafePtrTest, NullPtr)
{
	SafePtr<TestClass> ptr = {};

	ExpectTrue(ptr.IsCounterPtrNull());
	ExpectTrue(!ptr.IsValid());
}
TEST(SafePtrTest, Copy)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr<TestClass>();

	SafePtr<TestClass> copyConstructionPtr = SafePtr<TestClass>(ptr);
	SafePtr<TestClass> copyAssignmentPtr = {};
	copyAssignmentPtr = ptr;

	ExpectTrue(ptr.IsValid());
	ExpectTrue(copyConstructionPtr.IsValid());
	ExpectTrue(copyAssignmentPtr.IsValid());

	ExpectEqual(ptr.GetRaw(), copyConstructionPtr.GetRaw());
	ExpectEqual(ptr.GetRaw(), copyAssignmentPtr.GetRaw());
}
TEST(SafePtrTest, Move)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> refPtr = objRef.GetSafePtr<TestClass>();
	SafePtr<TestClass> a = objRef.GetSafePtr<TestClass>();
	SafePtr<TestClass> b = objRef.GetSafePtr<TestClass>();

	SafePtr<TestClass> aM = SafePtr<TestClass>(std::move(a));
	SafePtr<TestClass> bM = {};
	bM = std::move(b);

	ExpectTrue(a.IsCounterPtrNull());
	ExpectTrue(b.IsCounterPtrNull());
	ExpectFalse(aM.IsCounterPtrNull());
	ExpectFalse(bM.IsCounterPtrNull());

	ExpectFalse(a.IsValid());
	ExpectFalse(b.IsValid());
	ExpectTrue(aM.IsValid());
	ExpectTrue(bM.IsValid());

	ExpectEqual(refPtr.GetRaw(), aM.GetRaw());
	ExpectEqual(refPtr.GetRaw(), bM.GetRaw());
}
TEST(SafePtrTest, NullPtrCopyException)
{
	SafePtr<TestClass> ptr = {};
	SafePtr<TestClass> copyTarget;

	ExpectThrow(copyTarget = SafePtr<TestClass>(ptr), NullReferenceException);
	ExpectThrow(copyTarget = ptr, NullReferenceException);
}

TEST(SafePtrTest, Equality)
{
	SafeObjRef<TestClass> objRefA(new TestClass());
	SafeObjRef<TestClass> objRefB(new TestClass());
	SafePtr<TestClass> AA = objRefA.GetSafePtr<TestClass>();
	SafePtr<TestClass> AB = objRefA.GetSafePtr<TestClass>();
	SafePtr<TestClass> BA = objRefB.GetSafePtr<TestClass>();
	SafePtr<TestClass> CA;
	SafePtr<TestClass> CB;

	ExpectEqual(AA, AB);
	ExpectEqual(CA, CB);

	// Not using ExpectNotEqual to ensure we're testing equality operator
	ExpectFalse(AA == BA);
	ExpectFalse(AA == CA);
	ExpectFalse(BA == CA);
}

TEST(SafePtrTest, Inequality)
{
	SafeObjRef<TestClass> objRefA(new TestClass());
	SafeObjRef<TestClass> objRefB(new TestClass());
	SafePtr<TestClass> AA = objRefA.GetSafePtr<TestClass>();
	SafePtr<TestClass> AB = objRefA.GetSafePtr<TestClass>();
	SafePtr<TestClass> BA = objRefB.GetSafePtr<TestClass>();
	SafePtr<TestClass> CA;
	SafePtr<TestClass> CB;

	ExpectNotEqual(AA, BA);
	ExpectNotEqual(AA, CA);
	ExpectNotEqual(BA, CA);

	// Not using ExpectEqual to ensure we're testing inequality operator
	ExpectFalse(AA != AB);
	ExpectFalse(CA != CB);
}
TEST(SafePtrTest, Downcasting)
{
	SafeObjRef<Base> objRef(new Derived());
	SafePtr<Derived> ptr = objRef.GetSafePtr<Derived>();

	// This is a compile time operation, so if this compiles, we're good to go

	// This should not compile
	//SafePtr<NotDerived> oPtr = objRef.GetSafePtr<NotDerived>();
}