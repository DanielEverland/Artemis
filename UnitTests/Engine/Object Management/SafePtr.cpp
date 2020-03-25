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
TEST(SafePtrTest, NullPtr)
{
	SafePtr<TestClass> ptr = {};

	ExpectTrue(ptr.IsNull());
	ExpectTrue(!ptr.IsValid());
}
TEST(SafePtrTest, Copy)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> ptr = objRef.GetSafePtr();

	SafePtr<TestClass> copyConstructionPtr = SafePtr<TestClass>(ptr);
	SafePtr<TestClass> copyAssignmentPtr = {};
	copyAssignmentPtr = ptr;

	ExpectTrue(ptr.IsValid());
	ExpectTrue(copyConstructionPtr.IsValid());
	ExpectTrue(copyAssignmentPtr.IsValid());

	ExpectEqual(ptr.GetRaw(), copyConstructionPtr.GetRaw());
	ExpectEqual(ptr.GetRaw(), copyAssignmentPtr.GetRaw());
}
template<class T>
SafePtr<T>& MoveAssignmentTest()
{
	return SafePtr<T>();
}
TEST(SafePtrTest, Move)
{
	SafeObjRef<TestClass> objRef(new TestClass());
	SafePtr<TestClass> refPtr = objRef.GetSafePtr();
	SafePtr<TestClass> a = objRef.GetSafePtr();
	SafePtr<TestClass> b = objRef.GetSafePtr();

	SafePtr<TestClass> aM = SafePtr<TestClass>(std::move(a));
	SafePtr<TestClass> bM = {};
	bM = std::move(b);

	ExpectTrue(a.IsNull());
	ExpectTrue(b.IsNull());
	ExpectFalse(aM.IsNull());
	ExpectFalse(bM.IsNull());

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
