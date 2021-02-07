#include "pch.h"

#include "Modding/ModLoader.h"

namespace
{
	string TestFilesDir = GetTestFilesDir() + "/Entities/";
	string JsonKeyTestField = "TestField";
}

TEST(Modding, EntityTypeContainerSet)
{
	const string rawString = "test";
	const EntityType firstEntityType(rawString);
	const EntityType secondEntityType(rawString);
	std::set<EntityType> set = { };
	set.insert(firstEntityType);
	EXPECT_TRUE(set.contains(secondEntityType));
}

TEST(Modding, EntityTypeContainerMap)
{
	const string rawString = "test";
	const string valueString = "value";
	const EntityType firstEntityType(rawString);
	const EntityType secondEntityType(rawString);
	std::map<EntityType, string> map = { };
	map.insert(std::pair<EntityType, string>(firstEntityType, valueString));
	EXPECT_TRUE(map.contains(secondEntityType));
	EXPECT_EQ(map[secondEntityType], valueString);
}

TEST(Modding, LoadingEntities)
{
	ModLoader::LoadMods(TestFilesDir);
	const EntityType* characterType = ModLoader::GetType("Character");
	EXPECT_EQ("characterType", characterType->GetData().At<string>(JsonKeyName));
	EXPECT_EQ("base", characterType->GetData().At<string>(JsonKeyTestField));
}