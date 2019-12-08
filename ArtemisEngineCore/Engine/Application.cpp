#include "Application.h"

#include "Debugging/Output.h"

bool Application::useVSync = false;

void Application::SetVSync(bool enabled)
{
	useVSync = enabled;
}
bool Application::GetVSync()
{
	return useVSync;
}