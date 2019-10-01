#pragma once

#include <chrono>

#include "..\Windows\Window.h"

using std::chrono::high_resolution_clock;
using time_point = std::chrono::time_point<std::chrono::steady_clock>;
using std::chrono::nanoseconds;

class Time
{
public:
	inline static unsigned int GetFrameCount() { return frameCount; }
	inline static float GetDeltaTime() { return deltaTime; }

	static float GetTimeSinceStart();
	
private:
	static unsigned int frameCount;
	static high_resolution_clock clock;
	static nanoseconds initTime;
	static float deltaTime;

	static const double MillisecondToSeconds;
	
	friend void TickTime();
	friend void InitializeTime();
};