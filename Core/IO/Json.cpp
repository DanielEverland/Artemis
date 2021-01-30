#include "Json.h"

#include <fstream>

Json::Json()
{
}

Json Json::FromFile(const std::string& filePath)
{
	Json json;
	std::ifstream fileStream(filePath);

	fileStream >> json.rawJson;
	
	fileStream.close();

	return json;
}