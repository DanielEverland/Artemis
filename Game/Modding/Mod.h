#pragma once

#include <Game.h>

#include "ModInfo.h"

class Mod
{
public:
	Mod(const string& rootDirectory);

	static string ModInfoName;

private:
	string RootDirectory;
	ModInfo Info;

	void LoadModInfo();
	void VerifyModInfo() const;
	string GetModInfoFilePath() const;
};
