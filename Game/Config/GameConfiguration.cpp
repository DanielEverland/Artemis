#include "GameConfiguration.h"

#include <Game.h>

INIReader GameConfiguration::Reader = INIReader();

void GameConfiguration::Load()
{
	Reader = INIReader(Directory::GetProjectDirectory() + "Game.ini");
}

INIReader& GameConfiguration::GetReader()
{
	return Reader;
}
