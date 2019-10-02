#include "Time.h"

float Time::deltaTime = 0;
unsigned int Time::frameCount = 0;

float Time::GetTimeSinceStart()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&Time::currentTimeBuffer);

	return float((currentTimeBuffer - startTime) * Time::secondsPerCount);
}