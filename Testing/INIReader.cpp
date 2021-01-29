#include "pch.h"

#include <Core/Exceptions/IOException.h>
#include "INIReader/INISyntaxException.h"

string TestFilesDir = GetTestFilesDir() + "ini/";

TEST(INIReader, ValidFile)
{
	INIReader reader = INIReader(TestFilesDir + "ValidFile.ini");
	EXPECT_EQ("Value", reader.Get<string>("Test", "ThisIsAField", "DefaultValue"));
	EXPECT_EQ("SecondValue", reader.Get<string>("SecondCategory", "ThisIsAField", "DefaultValue"));
}

TEST(INIReader, ValidFileWithTrim)
{
	INIReader reader = INIReader(TestFilesDir + "ValidFile.ini");
	EXPECT_EQ("Value", reader.Get<string>("Test", "ThisIsAField", "DefaultValue"));
	EXPECT_EQ("SecondValue", reader.Get<string>("SecondCategory", "ThisIsAField", "DefaultValue"));
}

TEST(INIReader, GetInt)
{
	const int customDefaultValue = 69;
	
	INIReader reader = INIReader(TestFilesDir + "GetInt.ini");
	EXPECT_EQ(42, reader.Get<int>("Test", "Value", 0));
	EXPECT_EQ(42, reader.Get<int>("Test", "Value"));

	EXPECT_EQ(customDefaultValue, reader.Get<int>("Test", "MissingValue", customDefaultValue));
	EXPECT_EQ(customDefaultValue, reader.Get<int>("MissingCategory", "Value", customDefaultValue));

	EXPECT_EQ(0, reader.Get<int>("Test", "MissingValue"));
	EXPECT_EQ(0, reader.Get<int>("MissingCategory", "Value"));
}

TEST(INIReader, GetString)
{
	const string customDefaultValue = "defualt";

	INIReader reader = INIReader(TestFilesDir + "GetString.ini");
	EXPECT_EQ("value", reader.Get<string>("Test", "Value", ""));
	EXPECT_EQ("value", reader.Get<string>("Test", "Value"));

	EXPECT_EQ(customDefaultValue, reader.Get<string>("Test", "MissingValue", customDefaultValue));
	EXPECT_EQ(customDefaultValue, reader.Get<string>("MissingCategory", "Value", customDefaultValue));

	EXPECT_EQ("", reader.Get<string>("Test", "MissingValue"));
	EXPECT_EQ("", reader.Get<string>("MissingCategory", "Value"));
}

TEST(INIReader, GetDouble)
{
	const double customDefaultValue = 4.20;
	const double expectedValue = 2234567890123456789024.54;

	INIReader reader = INIReader(TestFilesDir + "GetDouble.ini");
	EXPECT_EQ(expectedValue, reader.Get<double>("Test", "Value", 0.0));
	EXPECT_EQ(expectedValue, reader.Get<double>("Test", "Value"));

	EXPECT_EQ(customDefaultValue, reader.Get<double>("Test", "MissingValue", customDefaultValue));
	EXPECT_EQ(customDefaultValue, reader.Get<double>("MissingCategory", "Value", customDefaultValue));

	EXPECT_EQ(0.0, reader.Get<double>("Test", "MissingValue"));
	EXPECT_EQ(0.0, reader.Get<double>("MissingCategory", "Value"));
}

TEST(INIReader, GetFloat)
{
	const float customDefaultValue = 4.20f;
	const float expectedValue = 3.14f;

	INIReader reader = INIReader(TestFilesDir + "GetFloat.ini");
	EXPECT_EQ(expectedValue, reader.Get<float>("Test", "Value", 0.0));
	EXPECT_EQ(expectedValue, reader.Get<float>("Test", "Value"));

	EXPECT_EQ(customDefaultValue, reader.Get<float>("Test", "MissingValue", customDefaultValue));
	EXPECT_EQ(customDefaultValue, reader.Get<float>("MissingCategory", "Value", customDefaultValue));

	EXPECT_EQ(0.0f, reader.Get<float>("Test", "MissingValue"));
	EXPECT_EQ(0.0f, reader.Get<float>("MissingCategory", "Value"));
}

TEST(INIReader, MisisngCategory)
{
	EXPECT_THROW(INIReader(TestFilesDir + "NoCategory.ini"), INISyntaxException);
}

TEST(INIReader, MissingStartBracket)
{
	EXPECT_THROW(INIReader(TestFilesDir + "MissingStartBracket.ini"), INISyntaxException);
}

TEST(INIReader, MissingEndBracket)
{
	EXPECT_THROW(INIReader(TestFilesDir + "MissingEndBracket.ini"), INISyntaxException);
}

TEST(INIReader, NoFile)
{
	EXPECT_THROW(INIReader("This is not a valid path"), IOException);
}

TEST(INIReader, DuplicateValues)
{
	EXPECT_THROW(INIReader(TestFilesDir + "DuplicateValues.ini"), INISyntaxException);
}

TEST(INIReader, NoEqualCharacter)
{
	EXPECT_THROW(INIReader(TestFilesDir + "NoEqualCharacter.ini"), INISyntaxException);
}

TEST(INIReader, TooManyEqualCharacters)
{
	EXPECT_THROW(INIReader(TestFilesDir + "TooManyEqualCharacters.ini"), INISyntaxException);
}