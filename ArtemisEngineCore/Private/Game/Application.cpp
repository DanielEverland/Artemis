#include "Public/Game/Application.h"
#include "Public/Game/Output.h"

using namespace ArtemisEngine;

bool Application::useVSync = false;

void Application::SetVSync(bool enabled)
{
	useVSync = enabled;
}
bool Application::GetVSync()
{
	return useVSync;
}