#include "GameConfiguration.h"

#include "IO/Directory.h"

using namespace ArtemisEngine;

INIReader GameConfiguration::Reader = INIReader();

void GameConfiguration::Load()
{
	Reader = INIReader(Directory::GetProjectDirectory() + "Game.ini");
}

INIReader& GameConfiguration::GetReader()
{
	return Reader;
}