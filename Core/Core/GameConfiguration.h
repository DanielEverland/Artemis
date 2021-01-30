#pragma once

class INIReader;

class GameConfiguration
{
public:
	static void Load();
	static INIReader& GetReader();

private:
	static INIReader Reader;
};
