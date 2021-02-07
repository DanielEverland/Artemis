#include "pch.h"

#include <string>

using std::string;

struct OverloadingData
{
	OverloadingData(string firstString, string secondString, int integer) : FirstString(firstString), SecondString(secondString), Integer(integer)
	{
	}
	OverloadingData(): Integer(0)
	{
	}

	string FirstString;
	string SecondString;
	int Integer;
	JSON_DEFINE(OverloadingData, FirstString, SecondString, Integer)
};

TEST(Json, MissingFields)
{
	const string firstString = "Test";
	
	json toDeserialize;
	toDeserialize["FirstString"] = firstString;

	OverloadingData data = toDeserialize.get<OverloadingData>();
	EXPECT_EQ(data.FirstString, firstString);
	EXPECT_EQ(data.SecondString, "");
	EXPECT_EQ(data.Integer, 0);
}

TEST(Json, OverloadingData)
{
	const string firstString = "first";
	const int firstInteger = 42;
	const string secondString = "second";
	const string stringNone = "none";

	OverloadingData firstData(firstString, "", firstInteger);
	
	const json firstJsonSerialized = firstData;
	const string firstJsonString = firstJsonSerialized.dump();

	const json firstJsonDeserialized = json::parse(firstJsonString);
	auto deserializedDataObject = firstJsonDeserialized.get<OverloadingData>();
	
	EXPECT_EQ(deserializedDataObject.FirstString, firstString);
	EXPECT_EQ(deserializedDataObject.SecondString, "");
	EXPECT_EQ(deserializedDataObject.Integer, firstInteger);

	const json secondJsonDeserialized = R"({
		"FirstString":"second",
		"SecondString":"none"})"_json;
	secondJsonDeserialized.get_to<OverloadingData>(deserializedDataObject);

	EXPECT_EQ(deserializedDataObject.FirstString, secondString);
	EXPECT_EQ(deserializedDataObject.SecondString, stringNone);
	EXPECT_EQ(deserializedDataObject.Integer, firstInteger);
}

TEST(Json, OverloadingRawJson)
{
	const string key = "key";
	const string firstString = "first";
	const string secondString = "second";

	const string firstRawJson = "{ \"" + key + "\" : \"" + firstString + "\" }";
	const string secondRawJson = "{ \"" + key + "\" : \"" + secondString + "\" }";

	Json data = Json::FromString(firstRawJson);
	const Json second = Json::FromString(secondRawJson);

	EXPECT_EQ(data.At<string>(key), firstString);
	
	data.Merge(second);

	EXPECT_EQ(data.At<string>(key), secondString);
}