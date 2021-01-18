#pragma once

#include <map>
#include <memory>

#include "DebugCategoryHandle.h"
#include "DebugCategory.h"

class GameplayDebugger
{
public:
	static const DebugCategoryHandle* CreateCategory();

private:
	static std::map<DebugCategoryHandle, DebugCategory> Categories;
};
