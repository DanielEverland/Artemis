#include <windows.h>

#include "Public/Game/Time.h"

float Time::deltaTime = 0;
float Time::secondsPerCount = 0;
unsigned int Time::frameCount = 0;
__int64 Time::startTime = 0;
__int64 Time::currentTimeBuffer = 0;

float Time::GetTimeSinceStart()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&Time::currentTimeBuffer);

	return float((currentTimeBuffer - startTime) * Time::secondsPerCount);
}