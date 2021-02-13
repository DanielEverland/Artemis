#pragma once

#include "../INIReader/INIReader.h"

class GameConfiguration
{
public:
	static void Load();
	static INIReader& GetReader();

private:
	static INIReader Reader;
};
