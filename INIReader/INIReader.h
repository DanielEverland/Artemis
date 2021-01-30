#pragma once

#include <map>
#include <string>

using std::map;
using std::string;

#define GET(category, valueName, defaultValue, converter) if(!Contains(category, valueName)) \
	return defaultValue; \
	return converter(values[category][valueName]);

class INIReader
{
public:
	explicit INIReader();
	explicit INIReader(const string& filePath);
	bool Contains(const string& category, const string& valueName);

	template<class T>
	T Get(const string& category, const string& valueName)
	{
		return Get<T>(category, valueName, T());
	}

	template<>
	string Get(const string& category, const string& valueName)
	{
		return Get<string>(category, valueName, "");
	}
	
	template<>
	int Get(const string& category, const string& valueName)
	{
		return Get<int>(category, valueName, 0);
	}

	template<>
	float Get(const string& category, const string& valueName)
	{
		return Get<float>(category, valueName, 0.f);
	}

	template<>
	double Get(const string& category, const string& valueName)
	{
		return Get<double>(category, valueName, 0.);
	}
	
	template<class T>
	T Get(const string& category, const string& valueName, T defaultValue);

	template<>
	string Get(const string& category, const string& valueName, string defaultValue);
	
	template<>
	int Get(const string& category, const string& valueName, int defaultValue);

	template<>
	float Get(const string& category, const string& valueName, float defaultValue);

	template<>
	double Get(const string& category, const string& valueName, double defaultValue);

private:
	map<string, map<string, string>> values;
	
	void ReadFile(const string& filePath);
	void LoadValue(string& line, const string& category);
	
	static bool IsCategoryLine(const string& line);
	static void CheckCategoryLine(const string& line);
	static void LoadCategoryLine(string& line, string& category);

	static void CheckValueLine(const string& line, const string& category);
};

template <class T>
T INIReader::Get(const string& category, const string& valueName, T defaultValue)
{
	GET(category, valueName, defaultValue, [](const string& value) -> T { return value; })
}
