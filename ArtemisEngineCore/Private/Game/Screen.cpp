#include "Public/Game/Screen.h"

unsigned int ArtemisEngine::Screen::height = 0;
unsigned int ArtemisEngine::Screen::width = 0;

unsigned ArtemisEngine::Screen::GetWidth()
{
	return width;
}

unsigned ArtemisEngine::Screen::GetHeight()
{
	return height;
}

float ArtemisEngine::Screen::GetAspectRatio()
{
	return static_cast<float>(width) / static_cast<float>(height);
}
