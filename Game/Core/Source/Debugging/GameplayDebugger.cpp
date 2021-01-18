#include "GameplayDebugger.h"

std::map<DebugCategoryHandle, DebugCategory> GameplayDebugger::Categories = { };

const DebugCategoryHandle* GameplayDebugger::CreateCategory()
{
	DebugCategoryHandle handle;
	Categories.insert(std::make_pair(handle, DebugCategory()));
	return &Categories.find(handle)->first;
}
