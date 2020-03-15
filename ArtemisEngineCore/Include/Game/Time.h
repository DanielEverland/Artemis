#pragma once

class Time
{
public:
	inline static unsigned int GetFrameCount() { return frameCount; }
	inline static float GetDeltaTime() { return deltaTime; }

	static float GetTimeSinceStart();
	
private:
	static unsigned int frameCount;
	static __int64 startTime;
	static __int64 currentTimeBuffer;
	static float deltaTime;
	static float secondsPerCount;
		
	friend void TickTime();
	friend void InitializeTime();
};