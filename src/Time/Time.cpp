#include "Time.h"

const double Time::MillisecondToSeconds = 1e-9;

double Time::deltaTime = 0;
unsigned int Time::frameCount = 0;
nanoseconds Time::initTime = {};

double Time::GetTimeSinceStart()
{
	auto now = clock.now();
	auto sinceEpoch = now.time_since_epoch();
	long long millisecondsSinceClockStart = (sinceEpoch - Time::initTime).count();

	return millisecondsSinceClockStart * MillisecondToSeconds;
}