#include "pch.h"

#include "Engine/ComponentContainer.h"

TEST(ComponentContainerTest, EmptyContainer)
{
	ComponentContainer container;

	ExpectEqual(0, container.GetCount());
}
TEST(ComponentContainerTest, AddComponent)
{
	ComponentContainer container;

	IComponent* testComponent = container.AddComponent<IComponent>();

	ExpectEqual(1, container.GetCount());
	ExpectTrue(testComponent != nullptr);
}