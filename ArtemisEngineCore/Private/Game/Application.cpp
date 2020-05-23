#include "Include/Game/Application.h"
#include "Include/Game/Output.h"

bool Application::useVSync = false;

void Application::SetVSync(bool enabled)
{
	useVSync = enabled;
}
bool Application::GetVSync()
{
	return useVSync;
}