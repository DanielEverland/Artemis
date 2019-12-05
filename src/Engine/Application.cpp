#include "Application.h"
#include <Debug/Output.h>
#include <Engine/Vector2.h>

bool Application::useVSync = false;

void Application::SetVSync(bool enabled)
{
	useVSync = enabled;

	using ArtemisEngine::Vector2;
	
	Vector2 a;
	a[0] = 45;
	a[1] = 32;

	Output::LogLine(a);
}
bool Application::GetVSync()
{
	return useVSync;
}