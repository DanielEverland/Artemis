#include "GameConfiguration.h"

#include <Core.h>

INIReader GameConfiguration::Reader = INIReader();

void GameConfiguration::Load()
{
	Reader = INIReader(Directory::GetProjectDirectory() + "Game.ini");
}

INIReader& GameConfiguration::GetReader()
{
	return Reader;
}
