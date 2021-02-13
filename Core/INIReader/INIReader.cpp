#include <fstream>
#include <algorithm>

#include <StringUtility.h>

#include "INIReader.h"
#include "INISyntaxException.h"
#include "../Exceptions/IOException.h"

using std::fstream;
using std::string;

INIReader::INIReader()
{
}

INIReader::INIReader(const string& filePath)
{
	ReadFile(filePath);
}

bool INIReader::Contains(const string& category, const string& valueName)
{
	return values.contains(category) &&  values[category].contains(valueName);
}

template <>
string INIReader::Get<string>(const string& category, const string& valueName, string defaultValue)
{
	GET(category, valueName, defaultValue, [](const string& value) -> string { return value; })
}

template <>
int INIReader::Get<int>(const string& category, const string& valueName, int defaultValue)
{
	GET(category, valueName, defaultValue, std::stoi)
}

template <>
float INIReader::Get<float>(const string& category, const string& valueName, float defaultValue)
{
	GET(category, valueName, defaultValue, std::stof)
}

template <>
double INIReader::Get<double>(const string& category, const string& valueName, double defaultValue)
{
	GET(category, valueName, defaultValue, std::stod)
}

void INIReader::ReadFile(const string& filePath)
{
	fstream file(filePath);
	if(!file.is_open())
		throw IOException("Couldn't open file " + filePath);

	string category;
	string line;
	while (std::getline(file, line))
	{
		trim(line);
		
		if(line.empty())
			continue;		

		if(IsCategoryLine(line))
		{
			CheckCategoryLine(line);
			LoadCategoryLine(line, category);
		}
		else
		{
			CheckValueLine(line, category);
			LoadValue(line, category);
		}
	}

	file.close();
}

void INIReader::LoadValue(string& line, const string& category)
{
	const size_t indexOfEqualCharacter = line.find('=');
	const string entry = line.substr(0, indexOfEqualCharacter);
	const string value = line.substr(indexOfEqualCharacter + 1, line.length() - 1);
	
	if(!values.contains(category))
		values.insert(values.begin(), std::pair<string, map<string, string>>(category, { }));

	if(values[category].contains(entry))
		throw INISyntaxException("Found existing entry " + entry + " in category " + category);

	values[category].insert(values[category].begin(), std::pair<string, string>(entry, value));
}

bool INIReader::IsCategoryLine(const string& line)
{
	return line[0] == '[';
}

void INIReader::CheckCategoryLine(const string& line)
{
	if(line[line.length() - 1] != ']')
		throw INISyntaxException("Last character in category line is not ]");
}

void INIReader::LoadCategoryLine(string& line, string& category)
{
	line.erase(0, 1);
	line.erase(line.length() - 1, 1);

	category = line;
}

void INIReader::CheckValueLine(const string& line, const string& category)
{
	if(category.empty())
		throw INISyntaxException("Found value \"" + line + "\" without a valid category");
	
	const size_t equalCharacterCount = std::count(line.begin(), line.end(), '=');
	if(equalCharacterCount != 1)
		throw INISyntaxException("Found an incorrect amount of equal characters (" + std::to_string(equalCharacterCount) + ") in value line");
}
