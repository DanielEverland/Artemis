#pragma once

#include <string>
#include <Windows.h>

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

namespace ArtemisEngine
{
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

		// Conversions from https://stackoverflow.com/a/59617138/3834696, slightly modified to fix warnings.
        static std::string ConvertWideToANSI(const std::wstring& wstr)
        {
            const int count = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), static_cast<int>(wstr.length()), nullptr, 0, nullptr, nullptr);
            std::string str(count, 0);
            WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], count, nullptr, nullptr);
            return str;
        }

        static std::wstring ConvertAnsiToWide(const std::string& str)
        {
            const int count = MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int>(str.length()), nullptr, 0);
            std::wstring wstr(count, 0);
            MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int>(str.length()), &wstr[0], count);
            return wstr;
        }

        static std::string ConvertWideToUtf8(const std::wstring& wstr)
        {
            const int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.length()), nullptr, 0, nullptr, nullptr);
            std::string str(count, 0);
            WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, nullptr, nullptr);
            return str;
        }

        static std::wstring ConvertUtf8ToWide(const std::string& str)
        {
            const int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.length()), nullptr, 0);
            std::wstring wstr(count, 0);
            MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.length()), &wstr[0], count);
            return wstr;
        }
	};
}