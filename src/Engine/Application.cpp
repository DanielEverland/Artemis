#include "Application.h"
#include <Debug/Output.h>

#include <Engine/Vector2.h>

bool Application::useVSync = false;

void Application::SetVSync(bool enabled)
{
	useVSync = enabled;
}
bool Application::GetVSync()
{
	return useVSync;
}