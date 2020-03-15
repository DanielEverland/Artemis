#pragma once

#include "Source/Game/Object Management/IObject.h"
#include "Source/Game/Object Management/GlobalObjectManager.h"

class Object : public IObject
{
public:
	Object() : uniqueID(GlobalObjectManager::CreateUniqueID())
	{
		GlobalObjectManager::RegisterID(GetUniqueID());
	}
	~Object()
	{
		GlobalObjectManager::RemoveID(GetUniqueID());
	}

	unsigned int GetUniqueID() const override;

private:
	const unsigned int uniqueID;
};