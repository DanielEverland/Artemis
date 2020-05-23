#pragma once

namespace ArtemisEngine
{
	class Screen
	{
	public:
		friend class GameWindow;

		static unsigned int GetWidth();
		static unsigned int GetHeight();
		static float GetAspectRatio();
		
	private:
		static unsigned int width;
		static unsigned int height;
	};
}
