#pragma once

#include <string>

#include "ModInfo.h"

using std::string;

class Mod
{
public:
	Mod(const string& rootDirectory);

	static string ModInfoName;

	void Load();

private:
	string RootDirectory;
	ModInfo Info;

	void LoadModInfo();
	void LoadAssets();
	void VerifyModInfo() const;
	[[nodiscard]] string GetModInfoFilePath() const;
};
