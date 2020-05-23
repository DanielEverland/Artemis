#include "Public/Game/Application.h"
#include "Public/Game/Output.h"

bool Application::useVSync = false;

void Application::SetVSync(bool enabled)
{
	useVSync = enabled;
}
bool Application::GetVSync()
{
	return useVSync;
}