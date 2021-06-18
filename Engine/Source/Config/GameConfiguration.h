#pragma once

#include "Core/INIReader.h"

namespace ArtemisEngine
{
	class GameConfiguration
	{
	public:
		static void Load();
		static INIReader& GetReader();

	private:
		static INIReader Reader;
	};
}
