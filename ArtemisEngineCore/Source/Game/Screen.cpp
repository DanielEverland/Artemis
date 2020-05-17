#include "Include/Game/Screen.h"

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
