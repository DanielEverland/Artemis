#pragma once

#include <unordered_set>

class GlobalObjectManager
{
public:
	static unsigned int CreateUniqueID();

	static void RegisterID(unsigned int id);
	static void RemoveID(unsigned int id);
	static bool IsIDRegistered(unsigned int id);

private:
	static unsigned int currentAvailableIndex;
	static std::unordered_set<unsigned int> objectRegistry;
};