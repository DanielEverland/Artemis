#include "Time.h"

#include "Application.h"

float Time::GetTime()
{
	return Application::Get()->GetTime();
}
