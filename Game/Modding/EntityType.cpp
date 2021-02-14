#include "EntityType.h"

#include "InvalidOperationException.h"
#include "ModLoader.h"

EntityType EntityType::Empty = EntityType("");

EntityType::EntityType(const string& typeString) : RawTypeString(typeString)
{
}

EntityType::EntityType(const string& typeString, const Json& prototype) : RawTypeString(typeString), Prototype(prototype)
{
}

string EntityType::GetType() const
{
	return Prototype.At<string>(JsonKeyType);
}

bool EntityType::IsBaseType() const
{
	return GetType() == BaseTypeName;
}

const EntityType* EntityType::GetBaseType() const
{
	if(IsBaseType())
		throw InvalidOperationException("Attempted to get base type of Base");

	return ModLoader::GetType(GetBaseTypeName());
}

string EntityType::GetBaseTypeName() const
{
	if(IsBaseType())
		throw InvalidOperationException("Attempted to get base type of Base");

	// Return default if none is explicitly specified
	if(!Prototype.Contains(JsonKeyBaseType))
		return BaseTypeName;

	return Prototype.At<string>(JsonKeyBaseType);
}

void EntityType::LoadData()
{
	Data = { };
	vector<const EntityType*> typeHierarchy = GetTypeHierarchy();
	for (const EntityType* type : typeHierarchy)
	{
		Data.Merge(type->GetPrototype());
	}
}

EntityType::operator string() const
{
	return ToString();
}

string EntityType::ToString() const
{
	return Data.At<string>("Name");
}

bool EntityType::IsAbstract() const
{
	return Prototype.At<bool>(JsonKeyIsAbstract);
}

vector<const EntityType*> EntityType::GetTypeHierarchy() const
{
	vector<const EntityType*> hierarchy;
	hierarchy.push_back(this);
	const EntityType* currentType = this;

	while (!currentType->IsBaseType())
	{
		currentType = currentType->GetBaseType();
		hierarchy.insert(hierarchy.begin(), currentType);
	}
	return hierarchy;
}

Json EntityType::GetPrototype() const
{
	return Prototype;
}

const Json* EntityType::GetData() const
{
	return &Data;
}

Json* EntityType::GetData()
{
	return &Data;
}

bool EntityType::IsEmpty() const
{
	return RawTypeString.empty();
}
