#pragma once

#include <string>

using std::string;

static void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

static void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}
class StringUtility
{
public:
	static void Trim(std::string& s)
	{
        ltrim(s);
        rtrim(s);
	}
    static string BoolToString(bool value)
    {
        return value ? "true" : "false";
    }
};