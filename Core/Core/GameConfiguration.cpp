#include "GameConfiguration.h"

#include <Core.h>

#include <INIReader.h>

void GameConfiguration::Load()
{
	Reader = INIReader(Directory::GetProjectDirectory() + "Game.ini");
}

INIReader& GameConfiguration::GetReader()
{
	return Reader;
}
