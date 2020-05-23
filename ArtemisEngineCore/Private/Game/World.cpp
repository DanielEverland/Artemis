#include "Public/Game/World.h"

#include "Public/Game/SafePtr.h"
#include "Public/Exceptions/NullReferenceException.h"

using namespace ArtemisEngine;

SafeObjRef<World> World::worldInstance = { };
list<SafeObjRef<IObject>> World::instantiatedObjects = { };
list<SafePtr<GameObject>> World::updateObjects = { };

SafePtr<World> World::GetWorld()
{
	if(!worldInstance.IsValid())
		throw NullReferenceException("No world has been created!");

	return worldInstance;
}

void World::UpdateState()
{
	for (auto backIter = updateObjects.crbegin(); backIter != updateObjects.crend(); ++backIter)
	{
		SafePtr<GameObject> updateObj = *backIter;

		if(!updateObj.IsValid())
			throw NullReferenceException("Found destroyed object in update loop!");

		updateObj->Update();
	}
}

void World::InstantiateObject(SafePtr<IObject> obj)
{
	auto* updateObject = dynamic_cast<GameObject*>(obj.GetRaw());
	if(updateObject != nullptr)
		AddToUpdateList(obj);

	obj->SetInstantiated(true);
	obj->Begin();
}

void World::AddToUpdateList(const SafePtr<GameObject>& updateObj)
{
	if(updateObj->ShouldUpdate())
		updateObjects.push_back(updateObj);
}