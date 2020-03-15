#include "pch.h"

#include "Engine/Object Management/ObjectContainer.h"
#include "Engine/SafePtr.h"

using namespace ArtemisEngine;

class TestClass
{
};

TEST(ObjectContainerTest, AddObject)
{
	ObjectContainer<TestClass> container;


	SafePtr<TestClass> ptr = container.Add();


	ExpectTrue(ptr.IsValid());
}
TEST(ObjectContainerTest, RemoveObject)
{
	ObjectContainer<TestClass> container;
	SafePtr<TestClass> ptr = container.Add();

		
	container.Remove(ptr);

	
	ExpectTrue(ptr.IsValid() == false);
}
TEST(ObjectContainerTest, RemoveObjectRaw)
{
	ObjectContainer<TestClass> container;
	SafePtr<TestClass> ptr = container.Add();
	TestClass* rawPtr = ptr;


	container.Remove(rawPtr);


	ExpectTrue(ptr.IsValid() == false);
}
TEST(ObjectContainerTest, Contains)
{
	ObjectContainer<TestClass> container;
	SafePtr<TestClass> ptr = container.Add();
	SafePtr<TestClass> emptyPtr;

	SafePtr<TestClass> removedPtr = container.Add();
	container.Remove(removedPtr);



	ExpectTrue(container.Contains(ptr));
	ExpectTrue(container.Contains(removedPtr) == false);
	ExpectTrue(container.Contains(emptyPtr) == false);
}
TEST(ObjectContainerTest, ContainsRaw)
{
	ObjectContainer<TestClass> container;
	TestClass* ptr = container.Add();
	TestClass* emptyPtr = nullptr;

	TestClass* removedPtr = container.Add();
	container.Remove(removedPtr);



	ExpectTrue(container.Contains(ptr));
	ExpectTrue(container.Contains(emptyPtr) == false);
	ExpectTrue(container.Contains(removedPtr) == false);
	ExpectTrue(container.Contains(nullptr) == false);
}
TEST(ObjectContainerTest, Destruction)
{
	ObjectContainer<TestClass>* container = new ObjectContainer<TestClass>();
	SafePtr<TestClass> ptr = container->Add();


	delete container;


	ExpectTrue(ptr.IsValid() == false);
}