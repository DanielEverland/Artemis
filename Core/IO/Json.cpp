#include <fstream>

#include "Json.h"
#include "../Exceptions/InvalidOperationException.h"

Json::Json()
{
}

Json Json::FromFile(const std::string& filePath)
{
	Json json;
	std::ifstream fileStream(filePath);

	fileStream >> json.RawJson;
	
	fileStream.close();

	return json;
}

Json Json::FromString(const string& rawString)
{
	Json json;
	json.RawJson = json::parse(rawString);
	return json;
}

bool Json::Contains(const string& key) const
{
	return RawJson.contains(key);
}

void Json::Merge(const Json& other)
{
	RawJson.merge_patch(other.RawJson);
}

json Json::GetRaw() const
{
	if(RawJson.empty())
		throw InvalidOperationException("RawJson is empty");

	return RawJson;
}
