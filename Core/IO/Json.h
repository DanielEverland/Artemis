#pragma once

#include <nlohmann/json.hpp>

using namespace nlohmann;

// Redefine to allow for missing fields in JSON strings
#define NLOHMANN_JSON_FROM(v1) if(nlohmann_json_j.contains(#v1)) { nlohmann_json_j.at(#v1).get_to(nlohmann_json_t.v1); }

#define JSON_DEFINE(Type, ...) NLOHMANN_DEFINE_TYPE_INTRUSIVE(Type, __VA_ARGS__)

class Json
{
public:
	Json();

	static Json FromFile(const std::string& filePath);

	template<class T>
	T Get();

	template<class T>
	T& GetTo(T& value);

private:
	json rawJson;
};

template <class T>
T Json::Get()
{
	return rawJson.get<T>();
}

template <class T>
T& Json::GetTo(T& value)
{
	return rawJson.get_to<T>(value);
}
