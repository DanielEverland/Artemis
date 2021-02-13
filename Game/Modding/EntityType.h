#pragma once

#include <string>
#include "../../Core/IO/Json.h"

using std::vector;
using std::string;

class EntityType
{
public:
	static EntityType Empty;

	explicit EntityType(const string& typeString);
	explicit EntityType(const string& typeString, const Json& prototype);

	void LoadData();

	[[nodiscard]] bool IsAbstract() const;
	[[nodiscard]] string GetType() const;
	[[nodiscard]] bool IsBaseType() const;
	[[nodiscard]] const EntityType* GetBaseType() const;
	[[nodiscard]] string GetBaseTypeName() const;
	[[nodiscard]] Json GetPrototype() const;
	[[nodiscard]] Json GetData() const;
	[[nodiscard]] bool IsEmpty() const;

	friend bool operator==(const EntityType& lhs, const EntityType& rhs)
	{
		return lhs.RawTypeString == rhs.RawTypeString;
	}

	friend bool operator!=(const EntityType& lhs, const EntityType& rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const EntityType& lhs, const EntityType& rhs)
	{
		return lhs.RawTypeString < rhs.RawTypeString;
	}

	friend bool operator<=(const EntityType& lhs, const EntityType& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const EntityType& lhs, const EntityType& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const EntityType& lhs, const EntityType& rhs)
	{
		return !(lhs < rhs);
	}

private:
	string RawTypeString;
	Json Prototype;
	Json Data;

	[[nodiscard]] vector<const EntityType*> GetTypeHierarchy() const;
};
