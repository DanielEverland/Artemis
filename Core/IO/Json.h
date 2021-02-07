#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "JsonMagicNumbers.h"

using std::string;

using namespace nlohmann;

// Redefine to allow for missing fields in JSON strings
#define NLOHMANN_JSON_FROM(v1) if(nlohmann_json_j.contains(#v1)) { nlohmann_json_j.at(#v1).get_to(nlohmann_json_t.v1); }

#define JSON_DEFINE(Type, ...) NLOHMANN_DEFINE_TYPE_INTRUSIVE(Type, __VA_ARGS__)

class Json
{
public:
	Json();

	static Json FromFile(const string& filePath);
	static Json FromString(const string& rawString);

	template<class T>
	T Get();

	template<class T>
	T At(const string& key) const;

	[[nodiscard]] bool Contains(const string& key) const;

	template<class T>
	T& GetTo(T& value);

	void Merge(const Json& other);

private:
	json GetRaw() const;
	
	json RawJson;
};

template <class T>
T Json::Get()
{	
	return GetRaw().get<T>();
}

template <class T>
T Json::At(const string& key) const
{
	return GetRaw().at(key);
}

template <class T>
T& Json::GetTo(T& value)
{
	return GetRaw().get_to<T>(value);
}
