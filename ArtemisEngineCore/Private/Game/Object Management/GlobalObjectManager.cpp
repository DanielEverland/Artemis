#include "GlobalObjectManager.h"
#include "Public/Exceptions/InvalidOperationException.h"

unsigned int GlobalObjectManager::currentAvailableIndex = 0;
std::unordered_set<unsigned int> GlobalObjectManager::objectRegistry = {};

unsigned int GlobalObjectManager::CreateUniqueID()
{
	return currentAvailableIndex++;
}
void GlobalObjectManager::RegisterID(unsigned int id)
{
	if (objectRegistry.find(id) != objectRegistry.end())
		throw InvalidOperationException("Attempted to register an ID which is already registered");

	objectRegistry.insert(id);
}
void GlobalObjectManager::RemoveID(unsigned int id)
{
	if(objectRegistry.find(id) != objectRegistry.end())
		throw InvalidOperationException("Attempted to remove an ID which is not registered");

	objectRegistry.erase(id);
}
bool GlobalObjectManager::IsIDRegistered(unsigned int id)
{
	return objectRegistry.find(id) != objectRegistry.end();
}